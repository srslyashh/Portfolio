var path = require('path');
var express = require('express');
var exphbs = require('express-handlebars')
var foodData = require('./foodData.json')
var fs = require('fs')

var app = express();
app.engine('handlebars', exphbs({ defaultLayout: 'main' }))
app.set('view engine', 'handlebars')

var port = 3000;

app.use(express.json())

app.get('/', function(req, res, next){
	res.status(200).render('mainpage')
})

app.get('/recipe', function (req, res, next) {
    res.status(200).render('recipesPage', {
			cards: foodData
		})
});

app.get('/recipe/:numRecipe', function(req,res){
	var reqIdx = req.params.numRecipe
	if(reqIdx >= 0 && reqIdx < foodData.length)
	{
		res.status(200).render('recipeView',  {
			recipe: foodData[reqIdx],
			partial: true
		})
	}
	else{
		res.status(404).render('404', {
	    page: req.url,
	    scripts: [ "/index.js" ]
	  })
	}
})

app.post('/recipe/addRecipe', function (req, res, next) {
  console.log("== req.body:", req.body)
  foodData.push({
    title: req.body.title,
    author: req.body.author,
    duration: req.body.duration,
    serving: req.body.serving,
    ingredients: req.body.ingredients,
    instructions: req.body.instructions,
    url: req.body.url,
		urlextension: req.body.urlextension
  })
    console.log("== foodData:", foodData)
    fs.writeFile(
      __dirname + '/foodData.json',
      JSON.stringify(foodData, null, 2),
      function (err) {
        if (err) {
          res.status(500).send("Error writing new data.  Try again later.")
        } else {
          res.status(200).send()
        }
      }
    )
})

app.use(express.static('public'));

app.get("*", function (req, res, next) {
  res.status(404).render('404', {
    page: req.url,
    scripts: [ "/index.js" ]
  });
});



app.listen(port, function (err) {
  if (err) {
    throw err;
  }
  console.log("== Server listening on port", port);
});
