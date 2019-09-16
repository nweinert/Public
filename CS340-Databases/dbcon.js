var mysql = require('mysql');
var pool = mysql.createPool({
  connectionLimit : 10,
  host            : 'classmysql.engr.oregonstate.edu',
  user            : 'cs340_weinertn',
  password        : '8008',
  database        : 'cs340_weinertn'
});

module.exports.pool = pool;
