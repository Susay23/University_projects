-- Cho lược đồ cơ sở dữ liệu về thư viện như sau:
-- TACPHAM(NT, tua, tacgia)
-- DOCGIA (ND, ho, ten, dchi, tel)
-- SACH (NS, nxb, NT)
-- MUON (NS, ngaymuon, hantra, ngaytra, ND) ;

create table TACPHAM(
    NT smallint primary key,
    tua nvarchar(50),
    tacgia nvarchar(50)
);

create table DOCGIA(
    ND smallint primary key,
    ho nvarchar(50),
    ten nvarchar(50),
    dchi nvarchar(100),
    tel char(50)
);

create table SACH(
    NS smallint primary key,
    nxb nvarchar(50),
    NT smallint not null,
    foreign key(NT) references TACPHAM(NT)
);

create table MUON(
    NS smallint not null,
    foreign key(NS) references SACH(NS),
    ngaymuon date not null,
    hantra date not null,
    ngaytra date,
    ND smallint not null,
    foreign key(ND) references DOCGIA(ND),
);

-- TACPHAM
INSERT INTO TACPHAM VALUES (1, N'Les misérables', N'Victor Hugo');
INSERT INTO TACPHAM VALUES (2, N'Germinal', N'Émile Zola');
INSERT INTO TACPHAM VALUES (3, N'Madame Bovary', N'Gustave Flaubert');
INSERT INTO TACPHAM VALUES (4, N'Les Fleurs du mal', N'Charles Baudelaire');
INSERT INTO TACPHAM VALUES (5, N'La Bête Humaine', N'Émile Zola');
INSERT INTO TACPHAM VALUES (6, N'Le Père Goriot', N'Honoré de Balzac');
INSERT INTO TACPHAM VALUES (7, N'Le Rouge et le Noir', N'Stendhal');
INSERT INTO TACPHAM VALUES (8, N'Une vie', N'Guy de Maupassant');
INSERT INTO TACPHAM VALUES (9, N'Ubu Roi', N'Alfred Jarry');
INSERT INTO TACPHAM VALUES (10, N'Poésies', N'Arthur Rimbaud');
INSERT INTO TACPHAM VALUES (11, N'La Mare au Diable', N'George Sand');
INSERT INTO TACPHAM VALUES (12, N'Carmen', N'Prosper Mérimée');
INSERT INTO TACPHAM VALUES (13, N'Lettres de mon moulin', N'Alphonse Daudet');
INSERT INTO TACPHAM VALUES (14, N'Les contes du chat perché', N'Marcel Aymé');
INSERT INTO TACPHAM VALUES (15, N'La Peste', N'Albert Camus');
INSERT INTO TACPHAM VALUES (16, N'Le petit prince', N'Antoine de St Exupéry');
-- DOCGIA
INSERT INTO DOCGIA VALUES (1, N'Lecoeur', N'Jeanette', N'16 rue de la République, 75010 Paris', '0145279274');
INSERT INTO DOCGIA VALUES (2, N'Lecoeur', N'Philippe', N'16 rue de la République, 75010 Paris', '0145279274');
INSERT INTO DOCGIA VALUES (3, N'Dupont', N'Yvan', N'73 rue Lamarck, 75018 Paris', '0163538294');
INSERT INTO DOCGIA VALUES (4, N'Mercier', N'Claude', N'155 avenue Parmentier, 75011 Paris', '0136482736');
INSERT INTO DOCGIA VALUES (5, N'Léger', N'Marc', N'90 avenue du Maine, 75014 Paris', '0164832947');
INSERT INTO DOCGIA VALUES (6, N'Martin', N'Laure', N'51 boulevard Diderot, 75012 Paris', '0174693277');
INSERT INTO DOCGIA VALUES (7, N'Crozier', N'Martine', N'88 rue des Portes Blanches, 75018 Paris', '0146829384');
INSERT INTO DOCGIA VALUES (8, N'Lebon', N'Clément', N'196 boulevard de Sébastopol, 75001 Paris', '0132884739');
INSERT INTO DOCGIA VALUES (9, N'Dufour', N'Jacques', N'32 rue des Alouettes, 75003 Paris', '0155382940');
INSERT INTO DOCGIA VALUES (10, N'Dufour', N'Antoine', N'32 rue des Alouettes, 75003 Paris', '0155382940');
INSERT INTO DOCGIA VALUES (11, N'Dufour', N'Stéphanie', N'32 rue des Alouettes, 75003 Paris', '0155382940');
INSERT INTO DOCGIA VALUES (12, N'Raymond', N'Carole', N'35 rue Oberkampf, 75011 Paris', '0153829402');
INSERT INTO DOCGIA VALUES (13, N'Durand', N'Albert', N'4 rue Mandar, 75002 Paris', '0642374021');
INSERT INTO DOCGIA VALUES (14, N'Wilson', N'Paul', N'12 rue Paul Vaillant Couturier, 92400 Montrouge', '0642327407');
INSERT INTO DOCGIA VALUES (15, N'Grecault', N'Philippe', N'15 rue de la Roquette, 75012 Paris', '0132762983');
INSERT INTO DOCGIA VALUES (16, N'Carre', N'Stéphane', N'51 boulevard Diderot, 75012 Paris', '0174693277');
INSERT INTO DOCGIA VALUES (17, N'Johnson', N'Astrid', N'3 rue Léon Blum, 75002 Paris', '0143762947');
INSERT INTO DOCGIA VALUES (18, N'Mirou', N'Caroline', N'2 square Mirabeau, 75011 Paris', '0163827399');
INSERT INTO DOCGIA VALUES (19, N'Espelette', N'Jean-Jacques', N'141 avenue de France, 75019 Paris', '0134887264');
INSERT INTO DOCGIA VALUES (20, N'Despentes', N'Anthony', N'56 boulevard de la Villette, 75019 Paris', '0133889463');
INSERT INTO DOCGIA VALUES (21, N'Terlu', N'Véronique', N'45 rue des Batignolles, 75020 Paris', '0165998372');
INSERT INTO DOCGIA VALUES (22, N'Rihour', N'Cécile', N'7 rue Montorgueil, 75002 Paris', '0166894754');
INSERT INTO DOCGIA VALUES (23, N'Franchet', N'Pierre', N'160 rue Montmartre, 75009 Paris', '0633628549');
INSERT INTO DOCGIA VALUES (24, N'Trochet', N'Ernest', N'34 rue de l''Esperance, 75008 Paris', '0638295563');
INSERT INTO DOCGIA VALUES (25, N'Gainard', N'Simon', N'55 rue Desnouettes, 75015 Paris', '0174928934');
INSERT INTO DOCGIA VALUES (26, N'Touche', N'Johanna', N'14 rue du Bac, 75006 Paris', '0619384065');
INSERT INTO DOCGIA VALUES (27, N'Cornu', N'Sylvain', N'22 rue Mouffetard, 75005 Paris', '0184927489');
INSERT INTO DOCGIA VALUES (28, N'Frederic', N'Cyril', N'15 rue du Simplon, 75018 Paris', '0173625492');
INSERT INTO DOCGIA VALUES (29, N'Crestard', N'Cedric', N'5 rue Doudeauville, 75018 Paris', '0629485700');
INSERT INTO DOCGIA VALUES (30, N'Le Bihan', N'Karine', N'170 bis rue Ordener, 75018 Paris', '0638995221');
-- SACH
INSERT INTO SACH VALUES (1, N'GF', 1);
INSERT INTO SACH VALUES (2, N'FOLIO', 2);
INSERT INTO SACH VALUES (3, N'HACHETTE', 3);
INSERT INTO SACH VALUES (4, N'GF', 4);
INSERT INTO SACH VALUES (5, N'FOLIO', 5);
INSERT INTO SACH VALUES (6, N'FOLIO', 6);
INSERT INTO SACH VALUES (7, N'GF', 7);
INSERT INTO SACH VALUES (8, N'FOLIO', 8);
INSERT INTO SACH VALUES (9, N'HACHETTE', 9);
INSERT INTO SACH VALUES (10, N'GF', 10);
INSERT INTO SACH VALUES (11, N'HACHETTE', 11);
INSERT INTO SACH VALUES (12, N'FOLIO', 12);
INSERT INTO SACH VALUES (13, N'GF', 13);
INSERT INTO SACH VALUES (14, N'FOLIO', 14);
INSERT INTO SACH VALUES (15, N'HACHETTE', 15);
INSERT INTO SACH VALUES (16, N'HACHETTE', 16);
INSERT INTO SACH VALUES (17, N'GF', 1);
INSERT INTO SACH VALUES (18, N'FOLIO', 2);
INSERT INTO SACH VALUES (19, N'HACHETTE', 2);
INSERT INTO SACH VALUES (20, N'FOLIO', 4);
INSERT INTO SACH VALUES (21, N'GF', 5);
INSERT INTO SACH VALUES (22, N'HACHETTE', 4);
INSERT INTO SACH VALUES (23, N'HACHETTE', 7);
INSERT INTO SACH VALUES (24, N'FOLIO', 8);
INSERT INTO SACH VALUES (25, N'GF', 1);
INSERT INTO SACH VALUES (26, N'HACHETTE', 10);
INSERT INTO SACH VALUES (27, N'FOLIO', 11);
INSERT INTO SACH VALUES (28, N'FOLIO', 12);
INSERT INTO SACH VALUES (29, N'GF', 1);
INSERT INTO SACH VALUES (30, N'HACHETTE', 14);

------------------------------------------------------------- 
-- +-------------------+              +-------------------+--
-- |     TACPHAM       |              |      DOCGIA       |--
-- +-------------------+              +-------------------+--
-- | PK | MaTacPham    |              | PK | MaDocGia     |--
-- |    | TenTacPham   |              |    | Ho           |--
-- |    | TacGia       |              |    | Ten          |--
-- +-------------------+              |    | DChi         |--
--           |                        |    | DThoai       |--
--           | 1                      +-------------------+--
--           |                                  |          --
--           | N                                | 1        --
-- +-------------------+                        |          --
-- |       SACH        |                        |          --
-- +-------------------+                        |          --
-- | PK | MaSach       |                        |          --
-- |    | NhaXuatBan   |                        | N        --
-- | FK | MaTacPham    | -------------> [ BẢNG TRUNG GIAN ]--
-- +-------------------+                 (Nếu có: MUON_TRA)--
--                                       - MaDocGia (FK)   --
--                                       - MaSach (FK)     --
-------------------------------------------------------------

-- 1) Xem dữ liệu của tất cả các bảng
-- 2) Vẽ sơ đồ liên thông
-- 3) Các tác phẩm (NT, tựa) của tác giả 'Guy de Maupassant'.
-- 4) Các độc giả sống ở địa chỉ '32 rue des Alouettes, 75003 Paris'.
-- 5) Tìm tên nhà xuất bản các tác phẩm bao gồm từ 'Fleur'
-- 6) Tìm tên các tác phẩm bắt đầu bằng 'Le'
-- 7) Tìm tên các độc giả có mượn sách trong trong khoảng thời gian từ ngày 15/9/2007 đến
-- 20/09/2007
-- 8) Nhà xuất bản của tác phẩm tiêu đề 'Germinal'.
-- 9) Tên độc giả đã mượn tác phẩm 'Poésie'.
-- 10) Những độc giả nào đã mượn tác phẩm Les 'Fleurs du mal'
-- 11) Tìm các tựa sách, tên độc giả của các độc giả trả sách quá thời hạn cho phép
-- 12) Tìm các tựa sách, tên độc giả của các độc giả trả sách trước thời hạn
-- 13) Tên độc giả đã mượn tác phẩm của 'Victor Hugo'
-- 14) Tên độc giả và các tác phẩm đã được mượn năm 2007
-- 15) Tính số tác phẩm có trong thư viện.
-- —------------------------------------------------------------------------------------------
-- 16) Tính Số sách của mỗi tác phẩm
-- 17) Tìm tên của tác phẩm mà có ít nhất hai quyển sách.
-- 18) Tìm tên tác phẩm có ít nhất 3 sách
-- 19) Tính Số tác phẩm của mỗi tác giả.
-- 20) Tính Số tác giả có ít nhất hai tác phẩm
-- 21) Tìm số lần mượn sách của mỗi độc giả theo năm
-- 22) Tìm tên tác phẩm có nhiều sách nhất
-- 23) Tên nhà xuất bản xuất bản nhiều sách nhất
-- 24) Tìm tên tác phẩm có ít nhất một quyển sách không ai mượn
-- 25) Tìm tên tác phẩm có tất cả các quyển sách đều được mượn
-- 26) Tìm họ tên độc giả chưa mượn quyển sách nào
-- 27) Tìm thông tin về nhà xuất bản của quyển sách mà chưa được ai mượn