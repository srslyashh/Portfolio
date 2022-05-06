(function() {
  var template = Handlebars.template, templates = Handlebars.templates = Handlebars.templates || {};
templates['recipeViewPartial'] = template({"compiler":[8,">= 4.3.0"],"main":function(container,depth0,helpers,partials,data) {
    var helper, alias1=depth0 != null ? depth0 : (container.nullContext || {}), alias2=container.hooks.helperMissing, alias3="function", alias4=container.escapeExpression, lookupProperty = container.lookupProperty || function(parent, propertyName) {
        if (Object.prototype.hasOwnProperty.call(parent, propertyName)) {
          return parent[propertyName];
        }
        return undefined
    };

  return "<main class=\"recipe-container\">	\n	<section class=\"recipe-view\">\n		<div class=\"img-container-view\">\n    		<!-- The <i> tag below includes the bullhorn icon from Font Awesome.  Do not directly style this element. -->\n	    	<img class=\"recipe-img-view\" src=\""
    + alias4(((helper = (helper = lookupProperty(helpers,"url") || (depth0 != null ? lookupProperty(depth0,"url") : depth0)) != null ? helper : alias2),(typeof helper === alias3 ? helper.call(alias1,{"name":"url","hash":{},"data":data,"loc":{"start":{"line":5,"column":40},"end":{"line":5,"column":47}}}) : helper)))
    + "\"/>\n		</div>\n    	<div class=\"recipe-title-view\">\n	    	"
    + alias4(((helper = (helper = lookupProperty(helpers,"title") || (depth0 != null ? lookupProperty(depth0,"title") : depth0)) != null ? helper : alias2),(typeof helper === alias3 ? helper.call(alias1,{"name":"title","hash":{},"data":data,"loc":{"start":{"line":8,"column":6},"end":{"line":8,"column":15}}}) : helper)))
    + "\n		</div>\n    	<div class=\"recipe-author-view\">\n        	"
    + alias4(((helper = (helper = lookupProperty(helpers,"author") || (depth0 != null ? lookupProperty(depth0,"author") : depth0)) != null ? helper : alias2),(typeof helper === alias3 ? helper.call(alias1,{"name":"author","hash":{},"data":data,"loc":{"start":{"line":11,"column":9},"end":{"line":11,"column":19}}}) : helper)))
    + "\n	    </div>\n		<div class=\"recipe-time-view\">\n			<i class=\"fas fa-clock\"></i> Time: "
    + alias4(((helper = (helper = lookupProperty(helpers,"duration") || (depth0 != null ? lookupProperty(depth0,"duration") : depth0)) != null ? helper : alias2),(typeof helper === alias3 ? helper.call(alias1,{"name":"duration","hash":{},"data":data,"loc":{"start":{"line":14,"column":38},"end":{"line":14,"column":50}}}) : helper)))
    + " mins\n	    </div>\n    	<div class=\"recipe-servings-view\">\n			<p><i class=\"fas fa-user-friends\"></i> serves "
    + alias4(((helper = (helper = lookupProperty(helpers,"serving") || (depth0 != null ? lookupProperty(depth0,"serving") : depth0)) != null ? helper : alias2),(typeof helper === alias3 ? helper.call(alias1,{"name":"serving","hash":{},"data":data,"loc":{"start":{"line":17,"column":49},"end":{"line":17,"column":60}}}) : helper)))
    + " </p>\n		</div>\n    	<div class=\"ingredients-header\">\n        	Ingredients\n	    </div>\n    	<div class=\"ingredients\">\n        	"
    + alias4(((helper = (helper = lookupProperty(helpers,"ingredients") || (depth0 != null ? lookupProperty(depth0,"ingredients") : depth0)) != null ? helper : alias2),(typeof helper === alias3 ? helper.call(alias1,{"name":"ingredients","hash":{},"data":data,"loc":{"start":{"line":23,"column":9},"end":{"line":23,"column":24}}}) : helper)))
    + "\n	    </div>\n		<div class=\"instructions-header\">\n			Instructions\n		</div>\n		<div class=\"instructions\">\n			"
    + alias4(((helper = (helper = lookupProperty(helpers,"intructions") || (depth0 != null ? lookupProperty(depth0,"intructions") : depth0)) != null ? helper : alias2),(typeof helper === alias3 ? helper.call(alias1,{"name":"intructions","hash":{},"data":data,"loc":{"start":{"line":29,"column":3},"end":{"line":29,"column":18}}}) : helper)))
    + "\n		</div>\n	</section>\n</main>";
},"useData":true});
})();