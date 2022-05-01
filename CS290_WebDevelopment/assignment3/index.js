/*
 * Add your JavaScript to this file to complete the assignment.  Don't forget
 * to add your name and @oregonstate email address below.
 *
 * Name: Kathleen Ashley
 * Email: ashleyk@oregonstate.edu
 */

// VARIABLE
var twitQuery = document.querySelectorAll('twit')

// VARIABLES FOR MODAL
var createTwitButton = document.getElementById('create-twit-button')
var modalBackdropEl = document.getElementById('modal-backdrop')
var createTwitModalEl = document.getElementById('create-twit-modal')

function unhideModal(event)
{
	if(createTwitModalEl.className == 'hidden')
	{
		modalBackdropEl.className = 'unhidden'
		createTwitModalEl.className = 'unhidden'
		twitInputEl.value = ""
		twitAuthorEl.value = ""
	}
	else if(createTwitModalEl.className == 'unhidden')
	{
		modalBackdropEl.className = 'hidden'
		createTwitModalEl.className = 'hidden'
		twitQuery = document.querySelectorAll('twit')
	}
}


// const toggles = Array.from(document.querySelectorAll('[data-search-toggle]'), (el) => {

// VARIABLES FOR SEARCH BAR
var navbarSearchInputEl = document.getElementById('navbar-search-input')
var navbarSearchButtonEl = document.getElementById('navbar-search-button')
var twitEl = document.getElementsByClassName('twit')
var authorArr = document.getElementsByClassName('twit-author')
var textArr = document.getElementsByClassName('twit-text')


function searchFunction(event)
{
	var currIndex
	var length = twitEl.length
	var count = 0

	for(var i = length - 1; i >= 0; i--)
	{
		var getInput = twitEl[i].childNodes[3].childNodes[1].textContent
		var getAuthorName = twitEl[i].childNodes[3].childNodes[3].textContent

		var lowerCaseTwit = getInput.toLowerCase()
		var lowerAuthorN = getAuthorName.toLowerCase()

		if(lowerCaseTwit.indexOf(navbarSearchInputEl.value.toLowerCase()) > -1 || lowerAuthorN.indexOf(navbarSearchInputEl.value.toLowerCase())> -1)
		{
			/*
			 for(var j = 0; j < authorArr.length; j++)
			 {
				 var holderAuthorLow = authorArr[j].textContent.toLowerCase()
				 if(holderAuthorLow == lowerAuthorN)
				 {
					 twitEl[i].add()
				 }
			 }
			 */
			 //twitEl[i].classList.remove('hidden')
		}
		else
		{
			 //twitEl[i].classList.add('hidden')
			twitEl[i].remove()
		}
	}
}

// VARIABLES FOR TWIT INPUT
var twitInputEl = document.getElementById('twit-text-input')
var twitAuthorEl = document.getElementById('twit-attribution-input')
var cancelButtonEl = document.getElementsByClassName('modal-cancel-button')[0]
var acceptButtonEl = document.getElementsByClassName('modal-accept-button')[0]
var closeButtonEl = document.getElementsByClassName('modal-close-button')[0]
var twitContainer = document.getElementsByClassName('twit-container')[0]

function generateTwitContainer(event)
{
	if(twitInputEl.value == "" || twitAuthorEl.value == "")
	{
		alert("You must specify both the text and the author of the twit!")
		return;
	}

	var twit = document.createElement('article')
	twit.classList.add('twit')

	// TWIT ICON
	var twitIconEl = document.createElement('div')
	twitIconEl.classList.add('twit-icon')

	// child of twitIconEl
	var bullhornIcon = document.createElement('i')
	bullhornIcon.classList.add('fa')
	bullhornIcon.classList.add('fa-bullhorn')

	twitIconEl.appendChild(bullhornIcon)

	// append to twit
	twit.appendChild(twitIconEl)

	// TWIT CONTENT
	var twitContentEl = document.createElement('div')
	twitContentEl.classList.add('twit-content')

	var twitTextEl = document.createElement('p')
	twitTextEl.classList.add('twit-text')
	twitTextEl.textContent = twitInputEl.value

	twitContentEl.appendChild(twitTextEl)

	// author
	var authorHolder = document.createElement('p')
	authorHolder.classList.add('twit-author')

	var twitAuthorElement = document.createElement('a')
	twitAuthorElement.href = '#'
	twitAuthorElement.textContent = twitAuthorEl.value

	// append authorElement to author holder.
	authorHolder.appendChild(twitAuthorElement)

	twitContentEl.appendChild(authorHolder)

	// APPEND TWITCONTENTEL TO TWIT
	twit.appendChild(twitContentEl)

	// make a twit container so we can insert
	// the contents inside
	twitContainer.appendChild(twit)

	unhideModal()
}

// EVENT LISTENER FOR TWIT INPUT
navbarSearchInputEl.addEventListener('input', searchFunction)

// EVENT LISTENER FOR MODAL
createTwitButton.addEventListener('click', unhideModal)
cancelButtonEl.addEventListener('click', unhideModal)
closeButtonEl.addEventListener('click', unhideModal)

// EVENT LISTENER FOR SEARCH BAR
acceptButtonEl.addEventListener('click', generateTwitContainer)
