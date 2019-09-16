module.exports = function(){
    var express = require('express');
    var router = express.Router();

    function getGenre(res, mysql, context, complete){
        mysql.pool.query("SELECT genreId, genreName FROM Genre", function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }
            context.genre  = results;
            complete();
        });
    }

    function getArtist(res, mysql, context, complete){
        mysql.pool.query("SELECT artistId, artistFirstName, artistLastName FROM Artist", function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }
            context.artist = results;
            complete();
        });
    }
	
    function getLabel(res, mysql, context, complete){
        mysql.pool.query("SELECT labelId, labelName FROM Record_Label", function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }
            context.label = results;
            complete();
        });
    }

    function getSongs(res, mysql, context, complete){
	mysql.pool.query("SELECT id, name, length, releaseYear, Record_Label.labelName as recordLabel FROM Song LEFT JOIN Record_Label on Record_Label.labelId = Song.labelId", 
		function(error, results, fields) {
			if(error) {
				res.write(JSON.stringify(error));
				res.end();
			}
			context.songs = results;
			complete();
		}
	);
    }

    function getSongsGenre(req, res, mysql, context, complete){
      var query = "SELECT Song.id, name, length, releaseYear, Record_Label.labelName as recordLabel, Genre.genreName FROM Song INNER JOIN Record_Label on Record_Label.labelId = Song.labelId INNER JOIN songsToGenres ON songsToGenres.songId = Song.id INNER JOIN Genre ON songsToGenres.genreId = Genre.genreId WHERE Genre.genreID = ?";
      var inserts = [req.params.genreId]
      mysql.pool.query(query, inserts, function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }
            context.songs = results;
            complete();
        });
    }

    function getSongsArtist(req, res, mysql, context, complete){
      var query = "SELECT Song.id, name, length, releaseYear, Record_Label.labelName as recordLabel, Artist.artistFirstName as fname, Artist.artistLastName as lname FROM Song INNER JOIN Record_Label on Record_Label.labelId = Song.labelId INNER JOIN songsToArtist ON songsToArtist.songId = Song.id INNER JOIN Artist ON songsToArtist.artistId = Artist.artistId WHERE Artist.artistID = ?";
      var inserts = [req.params.artistId]
      mysql.pool.query(query, inserts, function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }
            context.songs = results;
            complete();
        });
    }

 
    function getSongToUpdate(req, res, mysql, id, context, complete){
	var query = "SELECT s.id, s.name as name, s.length, s.releaseYear, rl.labelId, rl.labelName, g.genreId, a.artistId FROM Song s LEFT JOIN Record_Label rl ON s.labelId = rl.labelId LEFT JOIN songsToGenres ON s.id = songsToGenres.songId LEFT JOIN songsToArtist ON s.id = songsToArtist.songId LEFT JOIN Artist a on songsToArtist.artistId = a.artistId LEFT JOIN Genre g ON g.genreId = songsToGenres.genreId WHERE s.id = ?";
      var inserts = [id];
      mysql.pool.query(query, inserts, function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }
        console.log(results[0].length.substring(3,5), "sub 3-5", results[0].length.substring(6,8), "sub 6-8", results[0].length, "     =results[0].length");
	    var minutes = Number(results[0].length.substring(3,5));
	    var seconds = Number(results[0].length.substring(6,8));
	    context.time = {"min":minutes, "sec":seconds};
            context.song = results[0];
            console.log(context.song,"=song to update")
            complete();
        });
    }

   /*Display all people. Requires web based javascript to delete users with AJAX*/

    router.get('/', function(req, res){
        var callbackCount = 0;
        var context = {};
        var mysql = req.app.get('mysql');
        context.jsscripts = ["deletesong.js","filtersong.js"];
	getSongs(res, mysql, context, complete);
        getGenre(res, mysql, context, complete);
        getArtist(res, mysql, context, complete);
        getLabel(res, mysql, context, complete);
        function complete(){
            callbackCount++;
            if(callbackCount >= 4){
                res.render('songs', context);
            }

        }
    });

    /*Display all people from a given homeworld. Requires web based javascript to delete users with AJAX*/
    router.get('/genre/:genreId', function(req, res){
        var callbackCount = 0;
        var context = {};
        context.jsscripts = ["deletesong.js","filtersong.js"];
        var mysql = req.app.get('mysql');
        getSongsGenre(req,res, mysql, context, complete);
        getGenre(res, mysql, context, complete);
        getArtist(res, mysql, context, complete);
        getLabel(res, mysql, context, complete);
        function complete(){
            callbackCount++;
            if(callbackCount >= 4){
                res.render('songs', context);
            }

        }
    });

     router.get('/artist/:artistId', function(req, res){
        var callbackCount = 0;
        var context = {};
        context.jsscripts = ["deletesong.js","filtersong.js"];
        var mysql = req.app.get('mysql');
        getSongsArtist(req,res, mysql, context, complete);
        getGenre(res, mysql, context, complete);
        getArtist(res, mysql, context, complete);
        getLabel(res, mysql, context, complete);
        function complete(){
            callbackCount++;
            if(callbackCount >= 4){
                res.render('songs', context);
            }

        }
    });

    /* Display one person for the specific purpose of updating people */

    router.get('/:id', function(req, res){
        callbackCount = 0;
        var context = {};
        context.jsscripts = ["updatesong.js", "update.js"];
        var mysql = req.app.get('mysql');
        console.log(req.param.id,"    = req.param.id @get/:id" );
        getSongToUpdate(req, res, mysql, req.params.id, context, complete);
        getGenre(res, mysql, context, complete);
        getArtist(res, mysql, context, complete);
        getLabel(res, mysql, context, complete);
        function complete(){
            callbackCount++;
            if(callbackCount >= 4){
                res.render('updateSong', context);
            }

        }
    });

    /* Adds a person, redirects to the people page after adding */

    function getLastAddedSongId(req, res, mysql, lastId, complete2){
      var query = "SELECT id FROM Song ORDER BY id DESC LIMIT 1";
      mysql.pool.query("SELECT id FROM Song ORDER BY id DESC LIMIT 1", function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }
	    else {
	    lastId.value = results[0].id;
	    complete2();
	    }
        });
    }

    function getArtId(req, res, mysql, artId, curSongId, updateArtist){
	var query = "SELECT Artist.artistId FROM Artist INNER JOIN songsToArtist on Artist.artistId = songsToArtist.artistId WHERE songsToArtist.songId = ? ORDER BY Artist.artistId DESC LIMIT 1";
	var inserts = [curSongId]
	mysql.pool.query(query,inserts, function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }
	    else if(results[0] != undefined) {
		if (results[0].artistId != artId){
			updateArtist();
	        }
	    }
	    else {
		updateArtist();
	    }
        });
    }


    function getGenId(req, res, mysql, genId, curSongId, updateGenre){
	var query = "SELECT Genre.genreId FROM Genre INNER JOIN songsToGenres on Genre.genreId = songsToGenres.genreId WHERE songsToGenres.songId = ? ORDER BY Genre.genreId";
	var inserts = [curSongId]
	mysql.pool.query(query,inserts, function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }
	    else {
		for (let i = 0; i < results.length; i++){
			console.log("results[i] = ",results[i].gernreId);
			console.log("genId = ", genId);
			if(results[i].genreId == genId) {
				return;
			}
		}
		updateGenre();
	    }
        });
    }


    function insertSongsGenres(req, res, songId, genreId, mysql, complete) {
	var inserts = [songId, genreId];
	mysql.pool.query("INSERT INTO songsToGenres (songId, genreId) VALUES (?,?)",inserts,function(error, results, fields){
        	if(error){
        	    console.log(JSON.stringify(error))
        	    res.write(JSON.stringify(error));
        	    res.end();
        	}
		else {
		    complete();
		}
	});
    }


    function insertSongsArtist(req, res, songId, artistId, mysql, complete) {
	var inserts = [songId, artistId];
	mysql.pool.query("INSERT INTO songsToArtist (songId, artistId) VALUES (?,?)",inserts,function(error, results, fields){
        	if(error){
        	    console.log(JSON.stringify(error))
        	    res.write(JSON.stringify(error));
        	    res.end();
        	}
		else {
		    complete();
		}
	});
    }

    router.post('/', function(req, res){
    callbackCount = 0;
	//Create a time that we can enter into SQL
        var mysql = req.app.get('mysql');
	var minutes = "";
	var seconds = "";
	if(req.body.lengthMin < 10) {
		minutes = ":0" + req.body.lengthMin;
	} else {
		minutes = ":" + req.body.lengthMin;
	}
	if(req.body.lengthSec < 10) {
		seconds = ":0" + req.body.lengthSec;
	} else {
		seconds = ":" + req.body.lengthSec;
	}
	var newLength = "00" + minutes + seconds;
	//Store the artist and genre ID's for insertion into relationship tables
	var tmpArtistId = req.body.artist;
	var tmpGenreId = req.body.genre;
        var lastId = {};
        if (req.body.label=="NULL") {
            req.body.label = null;
        }
        var sql = "INSERT INTO Song (name, length, releaseYear, labelId) VALUES (?,?,?,?)";
        var inserts1 = [req.body.name, newLength, req.body.releaseYear, req.body.label];

        sql = mysql.pool.query(sql,inserts1,function(error, results, fields){
            if(error){
                console.log(JSON.stringify(error))
                res.write(JSON.stringify(error));
                res.end();
            }else{
		getLastAddedSongId(req, res, mysql, lastId, complete2);
	    }
	});
	function complete2() {
		console.log(lastId.value,"=last id val post");
		insertSongsGenres(req, res, lastId.value, tmpGenreId, mysql, complete);
		insertSongsArtist(req, res, lastId.value, tmpArtistId, mysql, complete);
	}
	function complete(){
	    callbackCount++;
	    if(callbackCount >= 2){
		res.redirect('/songs');
	    }
	}
    });

    /* The URI that update data is sent to in order to update a person */

    router.put('/:id', function(req, res){
	callbackCount = 0;
        var mysql = req.app.get('mysql');
	//callbackCount = 0;
 	//Create important vars
	var minutes = "";
	var seconds = "";
	if(req.body.lengthMin < 10) {
		minutes = ":0" + req.body.lengthMin;
	} else {
		minutes = ":" + req.body.lengthMin;
	}
	if(req.body.lengthSec < 10) {
		seconds = ":0" + req.body.lengthSec;
	} else {
		seconds = ":" + req.body.lengthSec;
	}
	var newLength = "00" + minutes + seconds;
	console.log(newLength, "=put length");
        if (req.body.label=="NULL") {
            req.body.label = null;
        }
    
	var sql = "UPDATE Song SET name=?, length=?, releaseYear=?, labelId=? WHERE id=?";
        var inserts = [req.body.name, newLength, req.body.releaseYear, req.body.label, req.params.id];
        sql = mysql.pool.query(sql,inserts,function(error, results, fields){
            if(error){
                console.log(error)
                res.write(JSON.stringify(error));
                res.end();
            }else{
		var artId = {};
		var genId = {};
		getArtId(req, res, mysql, req.body.artist, req.params.id, updateArtist)
		getGenId(req, res, mysql, req.body.genre, req.params.id, updateGenre)
	    }
	});
	function updateArtist() {
		var sql2 = "INSERT INTO songsToArtist (songId, artistId) VALUES (?,?)";
	        var inserts2 = [req.params.id, req.body.artist];
	        console.log(inserts2, "insert2");
	        sql2 = mysql.pool.query(sql2,inserts2,function(error, results, fields){
	            if(error){
	                console.log(error)
	                res.write(JSON.stringify(error));
	                res.end();
	            } else {
			complete;
		    }
		});
	}
	function updateGenre() {
		var sql3 = "INSERT INTO songsToGenres (songId, genreId) VALUES (?,?)";
	        var inserts3 = [req.params.id, req.body.genre];
	        console.log(inserts3, "insert3");
	        sql3 = mysql.pool.query(sql3,inserts3,function(error, results, fields){
	            if(error){
	                console.log(error)
	                res.write(JSON.stringify(error));
	                res.end();
	            } else {
			complete;
		    }
		});
	}
	function complete() {
		callbackCount++;
		if(callbackCount >= 2) {
			res.status(200);
			res.end();   
			console.log("no error complete put");
		}
	}
    });

  /* Route to delete a person, simply returns a 202 upon success. Ajax will handle this. */

    router.delete('/:id', function(req, res){
        var mysql = req.app.get('mysql');
        var sql1 = "DELETE FROM songsToArtist WHERE songId = ?";
        var inserts = [req.params.id];
        sql = mysql.pool.query(sql1, inserts, function(error, results, fields){
            if(error){
                console.log(error)
                res.write(JSON.stringify(error));
                res.status(400);
                res.end();
            }else{
	        var sql2 = "DELETE FROM songsToGenres WHERE songId = ?";
	        sql2 = mysql.pool.query(sql2, inserts, function(error, results, fields){
	            if(error){
	                console.log(error)
	                res.write(JSON.stringify(error));
	                res.status(400);
	                res.end();
	            }else{
			var sql3 = "DELETE FROM Song WHERE id = ?";
 			var inserts1 = [req.params.id];
 			sql3 = mysql.pool.query(sql3, inserts, function(error, results, fields){
 		           if(error){
 		               console.log(error)
 		               res.write(JSON.stringify(error));
 		               res.status(400);
 		               res.end();
 		           }else{
 		                res.status(202).end();
			   }
		        })
		    }
		})
	     }
        })
    })

    return router;

}();
