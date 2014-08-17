CREATE TABLE lamppeople (
	id INTEGER PRIMARY KEY AUTOINCREMENT,
	Name VARCHAR(255) NOT NULL,
	Statues INT NOT NULL
);

INSERT INTO lamppeople (Name, Statues) VALUES ('Sam',2),('Laura',1),('Chris',0);

Select Statues FROM lamppeople WHERE Name = "Sam";

UPDATE lamppeople SET Statues=1 WHERE Name="Sam";
