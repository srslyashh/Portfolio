# Assignment 2

**Assignment and Code Blog Entry due at 11:59pm on Monday 4/26/2021**<br />
**Demo due by 11:59pm on Monday 5/10/2021**

The goals of this assignment are to exercise your CSS skills and to give you practice at making a coded page match a set of provided mocks, which is a common task for a web developer.

Here, you are provided with an un-styled `index.html` file, an empty `style.css` file, and a set of mocks (actually screenshots/captures) in the `mocks/` directory.  Your task is to add styles to `style.css` to make your rendered `index.html` page matche the mocks as closely as possible.  Below are listed some of the things you must accomplish.

## Text styling

* The font for the entire page should be [Roboto](https://fonts.google.com/specimen/Roboto).  A third-party stylesheet is included in `index.html` to import this font from Google Fonts.

* Note the different font weights used across the page in the mocks.  The font weight in the header is different than the font weight of the each twit's text, which in turn is different than the font weight of each twit's author.

* Pay attention to text alignment in the various elements of the page.

## Navbar

* The links in the navbar should have space around them.

* The search box and search button should be pushed all the way to the right of the navbar, while the other links should remain on the left side.

* The "active" navbar link should be indicated with an underline.

* When the user hovers over the navbar links or the search button their color should change to highlight the hovered element.

* When the search box is focused, its background color should change to indicate its focus.  The unfocused search box should have a slightly dimmer background color.

## Twits

* The twit layout should be somewhat responsive to the size of the browser viewport, in that columns should be added and removed as the size of the browser viewport changes.  There should be a maximum of 3 columns.  Note that there should be equal space between all twits, both vertically and horizontally.

* Try to style your page so all twits in the same row have the same height.

* Pay attention to the alignment of elements within a single twit.  The top of the bullhorn icon should line up with the top of the twit text, and the right edge of the twit author should line up with the right edge of the twit itself (with just a bit of space between the edge of the author and the edge of the twit).

* Each twit should have a subtle border to help it stand out from the background.

* Note that the background behind the twits should not be pure white but a light gray.

* When the user hovers over a twit author, its color should change to highlight the hovered element.

## Add twit button

* The location of the "add twit" button should not not change relative to the viewport, even as the page is scrolled.

* The add twit button itself should be a perfect circle.

* The add twit button should have a subtle shadow behind it, to make it appear to be elevated slightly above the rest of the page.

* When the user hovers over the add twit button, it should grow slightly and change color to indicate its interactivity.  The mouse cursor should change to a pointing hand.  When implementing CSS to make the add twit button grow on hover, try to make it grow from the center instead of from the corner.

## Other notes on styling

Again, your goal is to match the mocks as closely as possible.  I'll show some tools in class that will help you do this.  Don't worry, however, if you don't get things like padding, margins, etc. exactly right.  Also, note that many style effects can be achieved in different ways using CSS.  However you implement various style features, the important thing is that they match the mocks as closely as possible.

One other thing to note is that the page incorporates several icons from the [Font Awesome icon library](https://fontawesome.com/icons?d=gallery).  This library is incorporated as a 3rd-party CSS file, and the icons are placed into the page using `<i>` elements whose HTML classes indicate which icon to display what icon style to use (e.g. `far`, `fas`, `fa-hand-lizard`, etc.).  Do not use these classes to apply styles to the page or apply styles directly to the `<i>` elements.  You should be apply styles to other elements to match the appearance of the mocks.

## Code blog

Add an entry to your Code Blog reflecting on your experience with this assignment.  Here are some questions you could answer (though these aren't the only ones):

  * What was challenging about the assignment, and what specific kinds of problems did you have.  How did you solve those problems?

  * What did you learn from the assignment?  Were there any special insights you had?  What did you find that you already knew?

  * What kinds of resources were helpful for completing the assignment?  Specific websites?  Lectures?  The class Piazza forum?  The TAs?  How did you use each of these resources?

  * What are one or two things you had to Google to complete the assignment?

## Submission

As always, we'll be using GitHub Classroom for this assignment, and you will submit your assignment via GitHub.  Just make sure your completed files are committed and pushed by the assignment's deadline to the master branch of the GitHub repo that was created for you by GitHub Classroom.  A good way to check whether your files are safely submitted is to look at the master branch your assignment repo on the github.com website (i.e. https://github.com/osu-cs290-sp21/assignment-2-YourGitHubUsername/). If your changes show up there, you can consider your files submitted.

In addition to submitting your assignment via GitHub, you must submit the URL to your code blog entry (e.g. http://web.engr.oregonstate.edu/~YOUR_ONID_ID/cs290/blog.html) via Canvas by the due date specified above.

## Grading criteria

Note that only changes to `style.css` will be considered when grading this assignment.  Any changes you make to `index.html` will be ignored.

The assignment is worth 100 points total:

* Color: 15 points
  * 15 points: colors for all elements match the mocks

* Text: 15 points
  * 5 points: font faces for all parts of the page (approximately) match the mocks
  * 5 points: text alignment and indentation matches the mocks
  * 5 points: all text sizes and weights match the mocks

* Layout: 25 points
  * 10 points: sizes of major components (header, nav, "twits", buttons, etc.) (approximately) match the mocks
  * 10 points: box sizes (margins, padding, borders) (approximately) matches the mocks
  * 5 points: relative locations of components (buttons, "twits", nav links, etc.) (approximately) matches the mocks

* Details: 35 points
  * 10 points: grid of "twits" properly displays in columns, and the number of columns decreases as the viewport shrinks
  * 5 points: hover effects for nav bar match the mocks and the description above
  * 5 points: static appearance (excluding interaction) of the "add twit" button matches the mocks
  * 5 points: hover effects for the "add twit" button match the mocks and the description above
  * 5 points: search box background changes when it has focus
  * 5 points: "active" navbar link is highlighted with a line underneath.

* Code style: 10 points
  * 5 points: white space and new lines are used appropriately for CSS readability
  * 5 points: CSS selectors maintain low complexity (i.e. they're only as specific as they need to be)

In addition to your programming assignment grade, you will receive a pass/fail grade for your code blog entry, included in the code blog portion of your grade.
