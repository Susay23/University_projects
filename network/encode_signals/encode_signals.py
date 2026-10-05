#!/usr/bin/env python3
"""
Mã hóa một đoạn văn bản thành tín hiệu và hiển thị ĐỒ THỊ ĐỘNG có PHÓNG TO / THU NHỎ.

Tín hiệu số (digital)       : NRZ-L, Manchester
Tín hiệu tuần tự (analog)   : ASK (biến điệu cường độ),
                              FSK (biến điệu tần số),
                              PSK (biến điệu pha)

Cách dùng:
    python encode_signals.py "Hello"
    python encode_signals.py "Văn bản dài ..." --window 24 --speed 2
    python encode_signals.py "Hi" --save out.gif      # lưu ảnh động (không có điều khiển)
Cài thư viện: pip install numpy matplotlib pillow

Điều khiển khi đang xem (cửa sổ tương tác):
    Cuộn chuột        : phóng to / thu nhỏ quanh vị trí con trỏ chuột
    Thanh "Phóng to / thu nhỏ" : chọn số bit hiển thị (từ 2 bit đến toàn bộ)
    Thanh "Vị trí"    : kéo để xem các đoạn khác của tín hiệu
    Phím + / -        : phóng to / thu nhỏ        Phím ← / → : di chuyển trái / phải
    Phím Space        : tạm dừng / phát tiếp / phát lại
    Phím F            : bám theo vị trí đang phát    Phím A : xem toàn bộ
    Phím [ / ]        : giảm / tăng tốc độ phát
    (Công cụ kính lúp / bàn tay trên thanh công cụ của matplotlib cũng dùng được)
"""
import argparse
import itertools
import math
from types import SimpleNamespace

import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation, PillowWriter
from matplotlib.widgets import Button, Slider

SAMPLES = 100          # số mẫu cho mỗi bit (Tb = 1 đơn vị thời gian)
MIN_VIEW = 2           # số bit tối thiểu khi phóng to
MAX_DETAIL = 80        # chỉ vẽ nhãn bit / đường kẻ bit khi đang xem <= số bit này

# Tham số điều chế
ASK_A1, ASK_A0 = 1.0, 0.3     # biên độ cho bit 1 / bit 0
CARRIER_F = 4                 # ASK, PSK: số chu kỳ sóng mang trong 1 bit
FSK_F1, FSK_F0 = 6, 3         # FSK: số chu kỳ trong 1 bit cho bit 1 / bit 0


def text_to_bits(text: str) -> np.ndarray:
    """Chuyển văn bản -> dãy bit (UTF-8, mỗi byte 8 bit, MSB trước)."""
    return np.array(
        [int(b) for byte in text.encode("utf-8") for b in format(byte, "08b")],
        dtype=int,
    )


def bits_to_text(bits) -> str:
    """Ghép lại các byte đã phát đầy đủ thành văn bản (để hiển thị tiến độ)."""
    n = len(bits) // 8
    data = bytes(int("".join(map(str, bits[i * 8:i * 8 + 8])), 2) for i in range(n))
    return data.decode("utf-8", errors="ignore")


# ---------------------------------------------------------------- Tín hiệu số
def nrz_l(bits):
    """NRZ-L: bit 1 -> mức +1, bit 0 -> mức -1 trong suốt chu kỳ bit."""
    return np.repeat(np.where(bits == 1, 1.0, -1.0), SAMPLES)


def manchester(bits):
    """Manchester (IEEE 802.3): bit 1 = chuyển từ thấp lên cao giữa bit,
    bit 0 = chuyển từ cao xuống thấp giữa bit."""
    half = SAMPLES // 2
    out = []
    for b in bits:
        first, second = (1.0, -1.0) if b == 1 else (-1.0, 1.0)
        out.append(np.full(half, first))
        out.append(np.full(SAMPLES - half, second))
    return np.concatenate(out)


# ------------------------------------------------------------ Tín hiệu tuần tự
def _time(bits):
    return np.arange(len(bits) * SAMPLES) / SAMPLES


def ask(bits):
    """ASK: thay đổi biên độ sóng mang theo bit."""
    t = _time(bits)
    amp = np.repeat(np.where(bits == 1, ASK_A1, ASK_A0), SAMPLES)
    return amp * np.sin(2 * np.pi * CARRIER_F * t)


def fsk(bits):
    """FSK: thay đổi tần số theo bit (pha liên tục)."""
    freq = np.repeat(np.where(bits == 1, FSK_F1, FSK_F0), SAMPLES)
    phase = 2 * np.pi * np.cumsum(freq) / SAMPLES
    return np.sin(phase)


def psk(bits):
    """BPSK: bit 1 -> pha 0, bit 0 -> pha pi."""
    t = _time(bits)
    phase = np.repeat(np.where(bits == 1, 0.0, np.pi), SAMPLES)
    return np.sin(2 * np.pi * CARRIER_F * t + phase) 


# ------------------------------------------------------------------- Hoạt hình
def build(text, bits, window, step, interval, loop=False, interactive=True):
    """Dựng đồ thị động. Trả về (fig, anim, ui)."""
    n = len(bits)
    total = n * SAMPLES
    t = _time(bits)
    specs = [
        ("NRZ-L (số)", nrz_l(bits), "tab:blue"),
        ("Manchester (số)", manchester(bits), "tab:cyan"),
        ("ASK - biến điệu cường độ", ask(bits), "tab:green"),
        ("FSK - biến điệu tần số", fsk(bits), "tab:orange"),
        ("PSK - biến điệu pha", psk(bits), "tab:red"),
    ]
    min_w = float(min(MIN_VIEW, n))

    # trạng thái chung của đồ thị
    state = dict(i=0,                       # số mẫu đã phát
                 width=float(min(window, n)),   # số bit đang hiển thị
                 lo=0.0,                    # mép trái của vùng xem
                 follow=True,               # bám theo vị trí đang phát
                 paused=False, done=False, touched=False,
                 step=step, busy=False, hold=0, running=True)

    if interactive:   # tránh phím tắt mặc định của matplotlib trùng với phím của ta
        plt.rcParams["keymap.fullscreen"] = []
        plt.rcParams["keymap.back"] = ["backspace"]
        plt.rcParams["keymap.forward"] = ["v"]
        plt.rcParams["keymap.home"] = ["h", "home"]

    fig, axes = plt.subplots(len(specs), 1, figsize=(14, 9), sharex=True)
    title = fig.suptitle("", fontsize=12)
    pool = MAX_DETAIL + 3

    lines, grids, cursors = [], [], []
    for ax, (name, _sig, color) in zip(axes, specs):
        (ln,) = ax.plot([], [], color=color, linewidth=1.6)
        lines.append(ln)
        ax.set_ylabel(name, rotation=0, ha="right", va="center", fontsize=9)
        ax.set_ylim(-1.5, 1.5)
        ax.axhline(0, color="gray", linewidth=0.5)
        grids.append([ax.axvline(0, color="gray", linestyle="--", linewidth=0.5)
                      for _ in range(pool)])
        cursors.append(ax.axvline(0, color="black", linewidth=1.2))
    axes[-1].set_xlabel("Thời gian (đơn vị: chu kỳ bit)")
    labels = [axes[0].text(0, 1.7, "", ha="center", va="bottom", fontweight="bold")
              for _ in range(pool)]
    fig.tight_layout(rect=(0.08, 0.2 if interactive else 0.0, 1, 0.95))

    ui = SimpleNamespace(state=state, fig=fig, axes=axes)

    # ------------------------------------------------------------ vẽ lại
    def render():
        i = state["i"]
        cur = i / SAMPLES
        w = min(max(state["width"], min_w), float(n))
        lo = max(0.0, cur - w) if state["follow"] else state["lo"]
        lo = min(max(lo, 0.0), n - w)
        hi = lo + w
        state.update(width=w, lo=lo)

        state["busy"] = True
        axes[0].set_xlim(lo, hi)
        state["busy"] = False

        # chỉ lấy phần dữ liệu đang nằm trong vùng xem cho nhẹ
        s0 = max(0, int(math.floor(lo)) - 1) * SAMPLES
        s1 = min(i, (int(math.ceil(hi)) + 1) * SAMPLES)
        for ln, (_nm, sig, _c) in zip(lines, specs):
            if s1 > s0:
                ln.set_data(t[s0:s1], sig[s0:s1])
            else:
                ln.set_data([], [])
        for c in cursors:
            c.set_xdata([cur, cur])

        detail = w <= MAX_DETAIL
        first_k = int(math.floor(lo))
        fs = 11 if w <= 24 else (8 if w <= 48 else 6)
        for j, lbl in enumerate(labels):
            k = first_k + j
            if detail and 0 <= k < n and k < cur and k < hi:
                lbl.set_position((k + 0.5, 1.7))
                lbl.set_text(str(bits[k]))
                lbl.set_fontsize(fs)
            else:
                lbl.set_text("")
        for grp in grids:
            for j, g in enumerate(grp):
                k = first_k + j
                g.set_visible(detail and 0 <= k <= n and lo <= k <= hi)
                g.set_xdata([k, k])

        done = min(int(cur), n)
        sent = bits_to_text(bits[:done])
        sent = ("…" + sent[-30:]) if len(sent) > 30 else sent
        shown = text if len(text) <= 30 else text[:27] + "..."
        title.set_text(f"Văn bản: '{shown}'  |  bit {done}/{n}  |  đã phát: '{sent}'"
                       f"  |  đang xem {w:.0f} bit")
        if interactive:
            sync_widgets(lo, w)

    def sync_widgets(lo, w):
        ui.zoom.eventson = False
        ui.zoom.set_val(math.log2(w))
        ui.zoom.eventson = True
        ui.zoom.valtext.set_text(f"{w:.0f} bit")
        ui.pos.eventson = False
        ui.pos.valmax = max(n - w, 1e-6)
        ui.pos.ax.set_xlim(ui.pos.valmin, ui.pos.valmax)
        ui.pos.set_val(min(lo, ui.pos.valmax))
        ui.pos.eventson = True
        ui.pos.valtext.set_text(f"bit {lo:.0f}")
        ui.btn_play.label.set_text("Phát lại" if state["done"]
                                   else ("Phát tiếp" if state["paused"] else "Tạm dừng"))

    # ---------------------------------------------- phóng to / thu nhỏ / di chuyển
    def set_width(new_w, anchor=None):
        old, lo = state["width"], state["lo"]
        new_w = min(max(new_w, min_w), float(n))
        if anchor is None:
            anchor = lo + old / 2
        frac = (anchor - lo) / old
        state.update(width=new_w, lo=anchor - frac * new_w, touched=True)
        render()
        fig.canvas.draw_idle()

    def pan(delta):
        state.update(follow=False, lo=state["lo"] + delta, touched=True)
        render()
        fig.canvas.draw_idle()

    def fit_all(_=None):
        state.update(width=float(n), lo=0.0, follow=False, touched=True)
        render()
        fig.canvas.draw_idle()

    def follow_now(_=None):
        state.update(follow=True, touched=True)
        render()
        fig.canvas.draw_idle()

    ui.set_width, ui.pan, ui.fit_all, ui.follow_now, ui.render = \
        set_width, pan, fit_all, follow_now, render

    # ----------------------------------------------------------- chạy / dừng
    def tick(_frame):
        if state["done"]:
            if loop:
                state["hold"] += 1
                if state["hold"] > 15:
                    restart()
            return
        if state["paused"]:
            return
        state["i"] = min(state["i"] + state["step"], total)
        if state["i"] >= total:
            finish()
        render()

    def finish():
        state["done"] = True
        state["follow"] = False
        if not state["touched"]:                  # chưa zoom thì hiện toàn bộ bit
            state.update(width=float(n), lo=0.0)
        if not loop:
            pause_anim()

    def restart():
        state.update(i=0, done=False, paused=False, follow=True, hold=0)
        play_anim()

    def pause_anim():
        if state["running"]:
            anim.pause()
            state["running"] = False

    def play_anim():
        if not state["running"]:
            anim.resume()
            state["running"] = True

    def toggle_pause(_=None):
        if state["done"]:
            restart()
        else:
            state["paused"] = not state["paused"]
            (pause_anim if state["paused"] else play_anim)()
        render()
        fig.canvas.draw_idle()

    # ------------------------------------------------------ điều khiển (widget)
    if interactive:
        ui.zoom = Slider(fig.add_axes([0.20, 0.115, 0.25, 0.025]), "Phóng to / thu nhỏ",
                         math.log2(min_w), math.log2(n), valinit=math.log2(state["width"]))
        ui.pos = Slider(fig.add_axes([0.68, 0.115, 0.25, 0.025]), "Vị trí",
                        0, max(n - state["width"], 1e-6), valinit=0)
        ui.btn_play = Button(fig.add_axes([0.20, 0.05, 0.12, 0.04]), "Tạm dừng")
        ui.btn_follow = Button(fig.add_axes([0.34, 0.05, 0.12, 0.04]), "Bám theo")
        ui.btn_all = Button(fig.add_axes([0.48, 0.05, 0.12, 0.04]), "Xem toàn bộ")
        fig.text(0.63, 0.06,
                 "Cuộn chuột: phóng to/thu nhỏ    ←/→: di chuyển    +/-: zoom\n"
                 "Space: tạm dừng    F: bám theo    A: toàn bộ    [ ]: tốc độ",
                 fontsize=8, va="center")

        ui.zoom.on_changed(lambda v: set_width(2 ** v))

        def on_pos(v):
            state.update(follow=False, lo=v, touched=True)
            render()
            fig.canvas.draw_idle()
        ui.pos.on_changed(on_pos)
        ui.btn_play.on_clicked(toggle_pause)
        ui.btn_follow.on_clicked(follow_now)
        ui.btn_all.on_clicked(fit_all)

        def on_scroll(ev):
            if ev.inaxes in axes:
                anchor = None if state["follow"] else ev.xdata
                set_width(state["width"] * (0.8 ** ev.step), anchor)

        def on_key(ev):
            k, w = ev.key, state["width"]
            if k in ("+", "=", "up"):
                set_width(w * 0.8)
            elif k in ("-", "_", "down"):
                set_width(w / 0.8)
            elif k == "left":
                pan(-0.1 * w)
            elif k == "right":
                pan(0.1 * w)
            elif k in (" ", "space"):
                toggle_pause()
            elif k in ("f", "F"):
                follow_now()
            elif k in ("a", "A"):
                fit_all()
            elif k == "]":
                state["step"] = min(state["step"] * 2, total)
            elif k == "[":
                state["step"] = max(1, state["step"] // 2)

        def on_xlim(ax):          # khi dùng kính lúp / bàn tay của thanh công cụ
            if state["busy"]:
                return
            lo, hi = ax.get_xlim()
            state.update(follow=False, lo=lo, width=hi - lo, touched=True)
            render()

        fig.canvas.mpl_connect("scroll_event", on_scroll)
        fig.canvas.mpl_connect("key_press_event", on_key)
        axes[0].callbacks.connect("xlim_changed", on_xlim)

        anim = FuncAnimation(fig, tick, frames=itertools.count(), interval=interval,
                             blit=False, cache_frame_data=False)
    else:
        frames = [(min(i, total), False) for i in range(step, total + step, step)]
        frames += [(total, True)] * 15            # khung cuối: hiện toàn bộ bit

        def update_saved(fr):
            i, final = fr
            state.update(i=i, follow=not final)
            if final:
                state.update(width=float(n), lo=0.0)
            render()
            return []

        anim = FuncAnimation(fig, update_saved, frames=frames, interval=interval,
                             blit=False, repeat=False)

    render()
    return fig, anim, ui


def main():
    parser = argparse.ArgumentParser(description="Mã hóa văn bản thành tín hiệu (động)")
    parser.add_argument("text", nargs="?", help="đoạn văn bản cần mã hóa")
    parser.add_argument("--window", type=int, default=None,
                        help="số bit hiển thị lúc đầu; mặc định = toàn bộ bit "
                             "(có thể phóng to / thu nhỏ khi đang xem)")
    parser.add_argument("--speed", type=float, default=1.0,
                        help="tốc độ phát (mặc định 1.0; 2.0 = nhanh gấp đôi)")
    parser.add_argument("--loop", action="store_true", help="lặp lại hoạt hình")
    parser.add_argument("--save", metavar="FILE.gif",
                        help="lưu hoạt hình ra file .gif thay vì hiển thị")
    args = parser.parse_args()

    text = args.text if args.text is not None else input("Nhập văn bản: ")
    if not text:
        print("Văn bản rỗng.")
        return

    bits = text_to_bits(text)
    print("Văn bản :", text)
    print("Chuỗi bit:", " ".join("".join(map(str, bits[i:i + 8]))
                                 for i in range(0, len(bits), 8)))
    print(f"Tổng cộng {len(bits)} bit")

    step = max(1, int(round(SAMPLES / 10 * args.speed)))   # mẫu mỗi khung hình
    interval = 30                                          # ms mỗi khung hình
    window = args.window or len(bits)
    fig, anim, _ui = build(text, bits, window, step, interval,
                           loop=args.loop and not args.save,
                           interactive=not args.save)

    if args.save:
        anim.save(args.save, writer=PillowWriter(fps=1000 // interval))
        print("Đã lưu", args.save)
    else:
        print("Điều khiển: cuộn chuột = zoom | ←/→ = di chuyển | Space = tạm dừng | "
              "F = bám theo | A = toàn bộ")
        plt.show()


if __name__ == "__main__":
    main()