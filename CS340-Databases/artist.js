module.exports = function(){
    var express = require('express');
    var router = express.Router();

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


   function getArtist(res, mysql, context, complete) {
        mysql.pool.query("SELECT artistFirstName, artistLastName, labelName FROM Artist INNER JOIN Record_Label on Record_Label.labelId = Artist.labelId", 
		function(error, results, fields){
	            if(error){
	                res.write(JSON.stringify(error));
	                res.end();
	            }
	            context.artist = results;
	            complete();
	        });
    }

    function getArtistGenre(req, res, mysql, context, complete){
      var query = "SELECT DISTINCT artistFirstName, artistLastName, Genre.genreName, labelName FROM Artist INNER JOIN Record_Label on Record_Label.labelId = Artist.labelId INNER JOIN songsToArtist ON Artist.artistId = songsToArtist.artistId INNER JOIN songsToGenres ON songsToArtist.songId = songsToGenres.songId INNER JOIN Genre on songsToGenres.genreId = Genre.genreId WHERE Genre.genreId = ?"
      var inserts = [req.params.genreId]
      mysql.pool.query(query, inserts, function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }
            context.artist = results;
            complete();
        });
    }

 
    /*Display all artists. Requires web based javascript to delete users with AJAX*/

    router.get('/', function(req, res){
        var callbackCount = 0;
        var context = {};
        context.jsscripts = ["filterartist.js"];
        var mysql = req.app.get('mysql');
        getLabel(res, mysql, context, complete);
	getGenre(res,mysql,context, complete);
	getArtist(res,mysql,context, complete);
        function complete(){
            callbackCount++;
            if(callbackCount >= 3){
                res.render('artist', context);
            }

        }
    });

    /*Display all artists from a given genre. Requires web based javascript to delete users with AJAX*/
    router.get('/filter/:genreId', function(req, res){
        var callbackCount = 0;
        var context = {};
        context.jsscripts = ["filterartist.js"];
        var mysql = req.app.get('mysql');
	getArtist(res,mysql,context, complete);
	getGenre(res,mysql,context, complete);
	getLabel(res,mysql,context, complete);
	getArtistGenre(req,res,mysql,context, complete);
        function complete(){
            callbackCount++;
            if(callbackCount >= 4){
                res.render('artist', context);
            }

        }
    });

    /* Adds an artist, redirects to the artist page after adding */

    router.post('/', function(req, res){
        console.log(req.body)
        var mysql = req.app.get('mysql');
        var sql = "INSERT INTO Artist (artistFirstName, artistLastName, labelId) VALUES (?,?,?)";
        var inserts = [req.body.fname, req.body.lname, req.body.label];
        sql = mysql.pool.query(sql,inserts,function(error, results, fields){
            if(error){
                console.log(JSON.stringify(error))
                res.write(JSON.stringify(error));
                res.end();
            }else{
                res.redirect('/artist');
            }
        });
    });

    return router;

}();
