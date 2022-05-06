function createRecipeCard(url, title, duration, serving) {

  var cardContext = {
    url: url,
    title: title,
    duration: duration,
    serving: serving
  }

  var recipeCardHTML = Handlebars.templates.recipeCard(cardContext)

  var cardContainer = document.querySelector('.card-container')
  cardContainer.insertAdjacentHTML('beforeend', recipeCardHTML)
}
