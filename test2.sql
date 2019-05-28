Create table books(
	ISBN char(17) Primary Key,
	name varchar(128) not null,
	pages int not null,
	price decimal(5,2),
	availble int not null,
	CONSTRAINT ISBN_con CHECK(ISBN LIKE '___-___-____-__-_')
);

Create table author_books(
	name varchar(64) references authors(name) ON DELETE CASCADE,
	email varchar(32) references authors(email) ON DELETE CASCADE,
	ISBN char(17) references books(ISBN) ON DELETE CASCADE,
	Primary Key(email, ISBN)
);

Create table Authors(
	name varchar(64),
	address varchar(64) not null,
	phone varchar(32) not null,
	bdate date not null,
	email varchar(32),
	CONSTRAINT au_email CHECK(email LIKE '%_@%_.%_'),
	Primary Key(name, email)
);

Create table readers(
	name varchar(64),
	email varchar(64),
	book_taken varchar(128) references books(ISBN) ON DELETE CASCADE,
	CONSTRAINT re_email CHECK(email LIKE '%_@%_.%_'),
	Primary Key(name, email)
);

Select ab.name, SUM(b.price)
	from books b join author_books ab on b.ISBN=ab.ISBN
	group by ab.name
	having SUM(b.price)>300

Insert into books (ISBN, name, pages, price, available) values ('123-456-7890-123-45', 'Test', '100', '99.99', '5')
Insert into Authors values ('John Smith', 'No where', '123-456-789-0', '1980-01-20', 'john_smith@madeup.com')

Update books b
	SET b.price = b.price + 10
	where b.ISBN in (select distinct ab.ISBN from author_books ab
					 where ab.name = 'John Smith')

Delete from books where name = 'Test'

Alter table readers add CONSTRAINT new_test DEFAULT 'John Doe' for name
Alter table readers drop CONSTRAINT new_test

Create view books_from_author
AS
select b.name, b.ISBN, ab.name as au_name, ab.email from books b
	join author_books ab on b.ISBN = ab.ISBN
GO

select name, au_name from books_from_author where au_name = 'Dante'
	
Create Trigger new_trig on books after Insert, Update
AS
	IF EXISTS (Select * from inserted where pages < 10)
	BEGIN
		ROLLBACK
	END
GO

Create Trigger stop_trig on books after Insert, Update, Delete
AS
	DECLARE @ins int = (Select Count(*) from inserted)
	IF @ins != 0 
	BEGIN
		ROLLBACK
	END
GO

Drop Trigger new_trig
