/*
 * Write your server code in this file.  Don't forget to add your name and
 * @oregonstate.edu email address below, so we know whose code we're grading.
 *
 * name: Kathleen Ashley
 * email: ashleyk@oregonstate.edu
 */

var fs = require('fs')
var http = require('http')
var counter = 0

// DEFAULT VALUE FOR PORT.
var port = 3000

if(process.env.PORT)
{
	port = process.env.PORT
}

// To ensure the files are only read once.
if(counter == 0)
{
	var indexdata = fs.readFileSync('./public/index.html', 'utf8')
	var styledata = fs.readFileSync('./public/style.css', 'utf8')
	var jsdata = fs.readFileSync('./public/index.js', 'utf8')
	var errdata = fs.readFileSync('./public/404.html', 'utf8')
	counter  = counter + 1
}

var server = http.createServer(function(req,res){
	if(req.url == '/index.html'|| req.url == '/')
	{
		res.statusCode = 200
		res.setHeader('Content-Type','text/html')
		res.write(indexdata)
		res.end()
	}
	else if(req.url == '/style.css')
	{
		res.statusCode = 200
		res.setHeader('Content-Type','text/css')
		res.write(styledata)
		res.end()
	}
	else if(req.url == '/index.js')
	{
		res.statusCode = 200
		res.setHeader('Content-Type','application/javascript')
		res.write(jsdata)
		res.end()
	}
	else if(req.url == '/404.html')
	{
		res.statusCode = 200
		res.setHeader('Content-Type','text/html')
		res.write(errdata)
		res.end()
	}
	else if(req.url == '/favicon.ico')
	{
		res.setHeader('Content-Type','image/jpeg')
		res.end()
	}
	else
	{
		res.statusCode = 404
		res.write(errdata)
		res.end()
	}
})

server.listen(port)
