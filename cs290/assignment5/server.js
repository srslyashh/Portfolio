 /*
 * Write your routing code in this file.  Make sure to add your name and
 * @oregonstate.edu email address below.
 *
 * Name: Kathleen Ashley
 * Email: ashleyk@oregonstate.edu
 */

var path = require('path');
var express = require('express');
var exphbs = require('express-handlebars');
var twitData = require('./twitData')

var app = express();
app.engine('handlebars', exphbs({ defaultLayout : 'main'}))
app.set('view engine', 'handlebars')

var port = process.env.PORT || 3000;

app.get('/', function(req,res){
	res.status(200).render('twitPage',  {
		twits: twitData,
		modalShow: true
	})
})

app.get('/twit/:index', function(req,res){
	var reqIdx = req.params.index
	if(reqIdx >= 0 && reqIdx < twitData.length)
	{
		res.status(200).render('twitPage',  {
			twits: twitData[reqIdx],
			singleTwit: true,
			modalShow: false
		})
	}
	else {
		res.status(404).render('404')
	}
})

app.use(express.static('public'));

app.get('*', function (req, res) {
  res.status(404).render('404')
});

app.listen(port, function (err) {
	if(err)
	{
		throw err
	}
  console.log("== Server is listening on port", port);
});
