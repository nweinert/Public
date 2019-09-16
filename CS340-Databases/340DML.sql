 .
--selections----------------------------
-- get all  IDs and Names to populate the artist dropdown
SELECT artistID, artistFirstName, artistFirstName  FROM Artist


--all genre names ids
SELECT genreID, genreName


--all labels
SELECT labelID, labelName, labelCity, labelState FROM Record_Label


--all Song
SELECT id, labelID, name, length, releaseYear FROM Song


--song name with artist name
SELECT a.artistFirstName , a.artistLastName, s.name 
	FROM Song s INNER JOIN songToArtist sa ON s.id = sa.songID  
	INNER JOIN Artist a ON a.artistID = sa.artistID


--song name with genre 
SELECT a.artistFirstName , a.artistLastName, g.genreName 
	FROM Song s INNER JOIN songToGenre sg ON s.id = sg.songID  
	INNER JOIN Genre g on g.genreID = sg.genreID

--artist name with record label name 
SELECT a.artistFirstName , a.artistLastName, r.labelName
	FROM Record_Label r INNER JOIN Artist a ON r.labelID = a.artistID  

	
--song name with record label name 

SELECT a.artistFirstName , a.artistLastName, r.labelName
	FROM Record_Label r INNER JOIN Song s ON r.labelID = s.id  

--INSERTS---------------  -->>    : indicates value to insert

INSERT INTO Artist (artistID, labelID, artistFirstName, artistLastName) VALUES (:artistIDInput, :labelIDInput, :artistFirstNameInput, :artistLastNameInput)

INSERT INTO Song (labelID, name, id, length, releaseYear) VALUES(:labelIDInput, :nameInput, :idInput, :lengthInput, :releaseYearInput )

INSERT INTO Record_Label (labelID, labelName, labelCity, labelState) VALUES(:labelIDInput, :labelNameInput, :labelCityInput, :lengthInput, :labelStateInput )

INSERT INTO Genre (genreID, genreName) VALUES(:genreIDInput, :genreNameInput)

INSERT INTO songToArtist (songID, artistID) VALUES(:songIDInput, :artistIDInput)

INSERT INTO songToGenre (songID, genreID) VALUES(:songIDInput, :genreIDInput)
 
 UPDATE Song SET (:labelIDInput, :nameInput, :idInput, :lengthInput, :releaseYearInput ) WHERE id= :songIDFromUpdateForm

DELETE FROM Song WHERE id= :songIDFromDeleteForm
 --dis-associate song from artist (M-to-M relationship deletion) 
 DELETE FROM SongToArtist sa WHERE sa.songID = :songIDFromDeleteForm AND sa.artistID = :artistIDFromDeleteForm





