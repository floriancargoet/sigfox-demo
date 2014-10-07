
var express    = require('express');
var bodyParser = require('body-parser');

// Server config
var HTTP_PORT = process.env.PORT || 5000;

// default color
var hexa = 'bada55';


var app = express();
app.use(bodyParser());
app.use(express.static(__dirname + '/public'));


app.post('/sigfox', function (req, res) {
  hexa = req.body.data;
  // nothing to return, just a 200 OK
  res.status(200).end();
});

app.get('/color', function (req, res) {
  res.send('#' + hexa);
});


// Starting server
console.log('[Server] Starting...');
app.listen(HTTP_PORT, function () {
  console.log('[Server] HTTP server is listening on port: ' + HTTP_PORT);
});
