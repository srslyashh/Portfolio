
var allCards = [];





function clearSearchAndReinsertCards() {
  document.getElementById('menubar-search-input').value = "";
  doSearchUpdate();
}


function cardMatchesSearchQuery(card, searchQuery) {

  if (!searchQuery) {
    return true;
  }


  searchQuery = searchQuery.trim().toLowerCase();
  return (card.ingredients).toLowerCase().indexOf(searchQuery) >= 0;
}

function insertNewCard(card)
{
  var templateContext = {
      title: card.title,
      duration: card.duration,
      serving: card.serving,
      ingredients: card.ingredients,
      instructions: card.instructions,
      author: card.author,
      url: card.url
  }

  var newCard = Handlebars.templates.recipeCard(templateContext)
  var recipeContainer = document.querySelector('.card-container')
  recipeContainer.insertAdjacentHTML('beforeend', newCard)
}





function doSearchUpdate() {

  var previousSearch = sessionStorage.getItem("lastSearch")
  var searchQuery = ''

  if (previousSearch != '') {
    searchQuery = previousSearch
  }
  else {
    searchQuery = document.getElementById('menubar-search-input').value;
  }
  sessionStorage.setItem("lastSearch", '');
  console.log(searchQuery)


  var cardContainer = document.querySelector('.card-container');
  if (cardContainer) {
    while (cardContainer.lastChild) {
      cardContainer.removeChild(cardContainer.lastChild);
    }
  }


  allCards.forEach(function (card) {
    if (cardMatchesSearchQuery(card, searchQuery)) {
      insertNewCard(card);
    }
  });
}

function homeSearch() {

  window.location.href = '/recipe';


}

function parseCardElem(cardElem) {
  var card = {};

  var cardImgElem = cardElem.querySelector('.recipe-img');
  card.url = cardImgElem.src;

  var cardTitleElem = cardElem.querySelector('.recipe-title');
  card.title = cardTitleElem.textContent.trim();

  var cardDurationElem = cardElem.querySelector('.recipe-time');
  // card.duration = cardDurationElem.textContent.match(/(\d+)/);

  var matchesDuration = cardDurationElem.textContent.match(/(\d+)/);
  if (matchesDuration) {
                card.duration = matchesDuration[0];
              }

  var cardServingElem = cardElem.querySelector('.recipe-servings');
  // card.serving = cardServingElem.textContent.match(/(\d+)/);

  var matchesServing = cardServingElem.textContent.match(/(\d+)/);
  if (matchesServing) {
                card.serving = matchesServing[0];
              }

  var cardIngredientsElem = cardElem.querySelector('.recipe-ingredients');
  card.ingredients = cardIngredientsElem.textContent.trim();

  var cardInstructionsElem = cardElem.querySelector('.recipe-instructions');
  card.instructions = cardInstructionsElem.textContent.trim();

  var cardAuthorElem = cardElem.querySelector('.recipe-author');
  card.author = cardAuthorElem.textContent.trim();

  return card;
}

function loadCards() {
    var cardElemsCollection = document.getElementsByClassName('recipe-card')
  for (var i = 0; i < cardElemsCollection.length; i++) {
    allCards.push(parseCardElem(cardElemsCollection[i]));
  }
}
//
// function pushCards() {
//     var cardElemsCollection = document.getElementsByClassName('recipe-card')
//     allCards.push(parseCardElem(cardElemsCollection[(cardElemsCollection.length)]));
// }




window.addEventListener('DOMContentLoaded', function () {


loadCards()

  var homeSearchButton = document.getElementById('search-button-home')


  var searchInput = document.getElementById('menubar-search-input');
    if (window.location.href.indexOf('/recipe') == -1) {
    searchInput.addEventListener('click', homeSearch);
    homeSearchButton.addEventListener('click', homeSearch)
    }
    searchInput.addEventListener('input', doSearchUpdate);


    // var homeSearchInput = document.getElementById('homepage-searchbar-input')
    //   if (homeSearchInput) {
    //     homeSearchInput.addEventListener('keyup', homeSearch)
    //   }
    })
    //
    // var titleInput = document.getElementById('title-input')
    // var ingredInput = document.getElementById('ingredients-input')
    // var instructInput = document.getElementById('instructions-input')
    // var durationInput = document.getElementById('duration-input')
    // var servingInput = document.getElementById('serving-input')
    // var authorInput = document.getElementById('author-input')
    // var urlInput = document.getElementById('url-input')
    // var recipeContainer = document.getElementsByClassName('recipebuilder')
    //
    //
    //
    //   function openRecipeCreate(event) {
    //     var menu = document.getElementById("create-recipe-modal")
    //     var recipeContainer = document.querySelector('.card-container')
    //     var button = document.getElementById("create-recipe-button")
    //     recipeContainer.classList.toggle('hidden')
    //     menu.classList.toggle('hidden')
    //
    //     button.classList.toggle('hidden')
    //     titleInput.value = ''
    //     ingredInput.value = ''
    //     instructInput.value = ''
    //     durationInput.value = ''
    //     servingInput.value = ''
    //     authorInput.value = ''
    //     urlInput.value = ''
    //   }
    //
    //   function clearRecipeCreate(event){
    //     titleInput.value = ''
    //     ingredInput.value = ''
    //     instructInput.value = ''
    //     durationInput.value = ''
    //     servingInput.value = ''
    //     authorInput.value = ''
    //     urlInput.value = ''
    //   }
    //
    //
    //
    //
    //
    //
    //
    //   function recipeCreate() {
    //
    //     titleInput = document.getElementById('title-input')
    //     ingredInput = document.getElementById('ingredients-input')
    //     instructInput = document.getElementById('instructions-input')
    //     durationInput = document.getElementById('duration-input')
    //     servingInput = document.getElementById('serving-input')
    //     authorInput = document.getElementById('author-input')
    //     urlInput = document.getElementById('url-input')
    //
    //     if(titleInput.value == '' || ingredInput.value == '' || instructInput.value == '' || durationInput.value == '' || servingInput.value == '' || authorInput.value == '' || urlInput.value == ''){
    //       alert("Please fill out all text boxes")
    //     }
    //     else {
    //
    //       var req = new XMLHttpRequest()
    //       var reqUrl = '/recipe/addRecipe'
    //       console.log("== reqUrl:", reqUrl)
    //       req.open('POST', reqUrl)
    //
    //       var ingredarray = document.getElementById('ingredients-input').value.split('\n');
    //       var instructarray = document.getElementById('instructions-input').value.split('\n');
    //
    //       var recipe = {
    //         title: titleInput.value,
    //         duration: durationInput.value,
    //         serving: servingInput.value,
    //         ingredients: ingredarray,
    //         instructions: instructarray,
    //         author: authorInput.value,
    //         url: urlInput.value
    //       }
    //       var reqBody = JSON.stringify(recipe)
    //       console.log("== reqBody:", reqBody)
    //       console.log("== reqBody.url:", reqBody.url)
    //       console.log("== typeof(reqBody):", typeof(reqBody))
    //
    //       req.setRequestHeader('Content-Type', 'application/json')
    //
    //       req.addEventListener('load', function (event) {
    //         if (event.target.status === 200) {
    //           var recipeCardTemplate = Handlebars.templates.recipeCard;
    //           var newRecipeCardHTML = recipeCardTemplate(recipe);
    //           var cardcontainer = document.querySelector('.card-container');
    //           cardcontainer.insertAdjacentHTML('beforeend', newRecipeCardHTML);
    //         } else {
    //           alert("Failed to add photo to database; error:\n\n" + event.target.response)
    //         }
    //       })
    //
    //       req.send(reqBody)
    //
    //       openRecipeCreate()
    //       pushCards()
    //     }
    //
    //   }
    //
    //
    //
    //
    //
    //   var button = document.getElementById("create-recipe-button")
    //   button.addEventListener('click', openRecipeCreate)
    //
    //
    //   var buttons = document.getElementsByClassName('modal-clear-button')
    //   for (var i = 0; i < buttons.length; i++) {
    //
    //     buttons[i].addEventListener('click', clearRecipeCreate)
    //   }
    //
    //   var buttons = document.getElementsByClassName('modal-accept-button')
    //   for (var i = 0; i < buttons.length; i++) {
    //     buttons[i].addEventListener('click', recipeCreate)
    //   }
    //
    //   var buttons = document.getElementsByClassName('modal-hide-button')
    //   for (var i = 0; i < buttons.length; i++) {
    //     buttons[i].addEventListener('click', openRecipeCreate)
    //   }
