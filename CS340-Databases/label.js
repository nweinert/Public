module.exports = function(){
    var express = require('express');
    var router = express.Router();

    function getLabel(res, mysql, context, complete){
         mysql.pool.query("SELECT rl.labelName, rl.labelCity, rl.labelState, s.stateName FROM Record_Label rl LEFT JOIN state s ON s.stateId = rl.labelState", function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }
            context.label = results;
            complete();
        });
    }

    function getState(res, mysql, context, complete) {
         mysql.pool.query("SELECT stateId, stateCode, stateName FROM state", function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }
            context.state = results;
            complete();
        });
    }
 
    router.get('/', function(req, res){
        var callbackCount = 0;
        var context = {};
        var mysql = req.app.get('mysql');
        getLabel(res, mysql, context, complete);
        getState(res, mysql, context, complete);
        function complete(){
            callbackCount++;
            if(callbackCount >= 2){
                res.render('label', context);
            }

        }
    });

    /* Adds a label, redirects to the people page after adding */

    router.post('/', function(req, res){
        console.log(req.body)
        var mysql = req.app.get('mysql');
        var sql = "INSERT INTO Record_Label (labelName, labelCity, labelState) VALUES (?,?,?)";
        var inserts = [req.body.name, req.body.city, req.body.state];
        sql = mysql.pool.query(sql,inserts,function(error, results, fields){
            if(error){
                console.log(JSON.stringify(error))
                res.write(JSON.stringify(error));
                res.end();
            }else{
                res.redirect('/label');
            }
        });
    });

    return router;

}();
