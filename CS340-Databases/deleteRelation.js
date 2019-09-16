module.exports = function(){
    var express = require('express');
    var router = express.Router();

    function getSA(res, mysql, context, complete){
        mysql.pool.query("SELECT a.artistId as artistId, a.artistFirstName as artistName, a.artistLastName, s.name as name, s.id as id FROM Artist a INNER JOIN songsToArtist sa ON sa.artistId = a.artistId INNER JOIN Song s ON id = sa.songId", function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }
            context.songsArtists = results;
            complete();
        });
    }

    function getSG(res, mysql, context, complete){
        mysql.pool.query("SELECT Genre.genreName as genreName, Genre.genreID as genreId, s.name as name, s.id as id FROM Genre INNER JOIN songsToGenres sg ON sg.genreId = Genre.genreId INNER JOIN Song s ON s.id = sg.songId", function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }
            context.songsGenres = results;
            complete();
        });
    }

    router.get('/', function(req, res){
        var callbackCount = 0;
        var context = {};
        var mysql = req.app.get('mysql');
        context.jsscripts = ["deleteRel.js"];
	getSA(res, mysql, context, complete);
	getSG(res, mysql, context, complete);
        function complete(){
            callbackCount++;
            if(callbackCount >= 2){
                res.render('delete_relation', context);
            }

        }
    });

    router.get('/genre/:id&:genreId', function(req, res){
        var mysql = req.app.get('mysql');console.log("genrerela here");
        var sql1 = "DELETE FROM songsToGenres WHERE songId = ? AND genreId = ?";
        var inserts = [req.params.id, req.params.genreId];console.log(req.params.id, req.params.genreId);
        sql = mysql.pool.query(sql1, inserts, function(error, results, fields){
            if(error){
                console.log(error)
                res.write(JSON.stringify(error));
                res.status(400);
                res.end();
            }else{
                res.status(202).end();
            }
	});
    })

    router.delete('/:id&:artistId', function(req, res){
        var mysql = req.app.get('mysql');
        var sql1 = "DELETE FROM songsToArtist WHERE songId = ? AND artistId = ?";
        var inserts = [req.params.id, req.params.artistId];
        sql = mysql.pool.query(sql1, inserts, function(error, results, fields){
            if(error){
                console.log(error)
                res.write(JSON.stringify(error));
                res.status(400);
                res.end();
	    }else{
 	        res.status(202).end();
	    }
	});
    })

    return router;
}();
