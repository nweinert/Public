module.exports = function(){
    var express = require('express');
    var router = express.Router();

   function getGenre(res, mysql, context, complete) {
        mysql.pool.query("SELECT genreName FROM Genre", 
		function(error, results, fields){
	            if(error){
	                res.write(JSON.stringify(error));
	                res.end();
	            }
	            context.genre = results;
	            complete();
	        });
    }

    /*Display all people. Requires web based javascript to delete users with AJAX*/
    router.get('/', function(req, res){
        var callbackCount = 0;
        var context = {};
        var mysql = req.app.get('mysql');
        getGenre(res, mysql, context, complete);
        function complete(){
            callbackCount++;
            if(callbackCount >= 1){
                res.render('genre', context);
            }

        }
    });

    /* Adds a person, redirects to the people page after adding */
    router.post('/', function(req, res){
        console.log(req.body)
        var mysql = req.app.get('mysql');
        var sql = "INSERT INTO Genre (genreName) VALUES (?)";
        var inserts = [req.body.name];
        sql = mysql.pool.query(sql,inserts,function(error, results, fields){
            if(error){
                console.log(JSON.stringify(error))
                res.write(JSON.stringify(error));
                res.end();
            }else{
                res.redirect('/genre');
            }
        });
    });

    return router;

}();
