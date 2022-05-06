var titleInput = document.getElementById('title-input')
var ingredInput = document.getElementById('ingredients-input')
var instructInput = document.getElementById('instructions-input')
var durationInput = document.getElementById('duration-input')
var servingInput = document.getElementById('serving-input')
var authorInput = document.getElementById('author-input')
var urlInput = document.getElementById('url-input')
var recipeContainer = document.getElementsByClassName('recipebuilder')



function openRecipeCreate(event) {
  var menu = document.getElementById("create-recipe-modal")
  var recipeContainer = document.querySelector('.card-container')
  var button = document.getElementById("create-recipe-button")
  recipeContainer.classList.toggle('hidden')
  menu.classList.toggle('hidden')

  button.classList.toggle('hidden')
  titleInput.value = ''
  ingredInput.value = ''
  instructInput.value = ''
  durationInput.value = ''
  servingInput.value = ''
  authorInput.value = ''
  urlInput.value = ''
}


function clearRecipeCreate(event){
  titleInput.value = ''
  ingredInput.value = ''
  instructInput.value = ''
  durationInput.value = ''
  servingInput.value = ''
  authorInput.value = ''
  urlInput.value = ''
}


function recipeCreate() {

  titleInput = document.getElementById('title-input')
  ingredInput = document.getElementById('ingredients-input')
  instructInput = document.getElementById('instructions-input')
  durationInput = document.getElementById('duration-input')
  servingInput = document.getElementById('serving-input')
  authorInput = document.getElementById('author-input')
  urlInput = document.getElementById('url-input')
  var recipeCard = document.getElementsByClassName('recipe-card')
  var dataLength = recipeCard.length

  if(titleInput.value == '' || ingredInput.value == '' || instructInput.value == '' || durationInput.value == '' || servingInput.value == '' || authorInput.value == '' || urlInput.value == ''){
    alert("Please fill out all text boxes")
  }
  else {

    var req = new XMLHttpRequest()
    var reqUrl = '/recipe/addRecipe'
    console.log("== reqUrl:", reqUrl)
    req.open('POST', reqUrl)

    var ingredarray = document.getElementById('ingredients-input').value.split('\n');
    var instructarray = document.getElementById('instructions-input').value.split('\n');

    var recipe = {
      title: titleInput.value,
      duration: durationInput.value,
      serving: servingInput.value,
      ingredients: ingredarray,
      instructions: instructarray,
      author: authorInput.value,
      url: urlInput.value,
      urlextension: dataLength
    }
    var reqBody = JSON.stringify(recipe)
    console.log("== reqBody:", reqBody)
    console.log("== reqBody.url:", reqBody.url)
    console.log("== typeof(reqBody):", typeof(reqBody))

    req.setRequestHeader('Content-Type', 'application/json')

    req.addEventListener('load', function (event) {
      if (event.target.status === 200) {
        var recipeCardTemplate = Handlebars.templates.recipeCard;
        var newRecipeCardHTML = recipeCardTemplate(recipe);
        var cardcontainer = document.querySelector('.card-container');
        cardcontainer.insertAdjacentHTML('beforeend', newRecipeCardHTML);
      } else {
        alert("Failed to add photo to database; error:\n\n" + event.target.response)
      }
    })

    req.send(reqBody)

    openRecipeCreate()

  }

}





var button = document.getElementById("create-recipe-button")
button.addEventListener('click', openRecipeCreate)


var buttons = document.getElementsByClassName('modal-clear-button')
for (var i = 0; i < buttons.length; i++) {

  buttons[i].addEventListener('click', clearRecipeCreate)
}

var buttons = document.getElementsByClassName('modal-accept-button')
for (var i = 0; i < buttons.length; i++) {
  buttons[i].addEventListener('click', recipeCreate)
}

var buttons = document.getElementsByClassName('modal-hide-button')
for (var i = 0; i < buttons.length; i++) {
  buttons[i].addEventListener('click', openRecipeCreate)
}
