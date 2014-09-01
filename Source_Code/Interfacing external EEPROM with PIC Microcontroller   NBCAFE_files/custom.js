jQuery(document).ready(function() {

jQuery('aside.home-feat-cat:nth-child(2n+1)').addClass('odd');
jQuery('#right-sidebar #wp-calendar').wrap('<div class="extra-block">');
jQuery('#right-sidebar .widget_categories select').wrap('<div class="extra-block">');
jQuery('#right-sidebar .widget_archive select').wrap('<div class="extra-block">');
jQuery('#featuredbox').delay(2000).fadeIn(400);

jQuery("ul.sf-menu").supersubs({
            minWidth:    18,
            maxWidth:    18,
            extraWidth:  1
        }).superfish();
});


document.write('<style type="text/css">.tabber{display:none;}<\/style>');

function startGallery() {
var myGallery = new gallery($('myGallery'), {
timed: true,
delay: 8000,
showArrows: true,
showCarousel: false,
embedLinks: true
});
document.gallery = myGallery;
}
if (typeof onDomReady == 'function') {
window.onDomReady(startGallery);
}