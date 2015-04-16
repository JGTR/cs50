/**
 * scripts.js
 *
 * Computer Science 50
 * Problem Set 8
 *
 * Global JavaScript.
 */

// Google Map
var map;

// markers for map
var markers = [];

// info window
var info = new google.maps.InfoWindow();

// Store user's geolocation
var myposition = 0;


// execute when the DOM is fully loaded
$(function() {

    // styles for map
    // https://developers.google.com/maps/documentation/javascript/styling
    var styles = [

        // hide Google's labels
        {
            featureType: "all",
            elementType: "labels",
            stylers: [
                {visibility: "off"}
            ]
        },

        // hide roads
        {
            featureType: "road",
            elementType: "geometry",
            stylers: [
                {visibility: "off"}
            ]
        }

    ];


    // options for map
    // https://developers.google.com/maps/documentation/javascript/reference#MapOptions


    var options = {
        center: {lat: 42.3770, lng: -71.1256}, // Cambridge, Massachusetts
        disableDefaultUI: true,
        mapTypeId: google.maps.MapTypeId.ROADMAP,
        maxZoom: 14,
        panControl: true,
        styles: styles,
        zoom: 13,
        zoomControl: true
    };

    // get DOM node in which map will be instantiated
    var canvas = $("#map-canvas").get(0);

    // instantiate map
    map = new google.maps.Map(canvas, options);

    // configure UI once Google Map is idle (i.e., loaded)
    google.maps.event.addListenerOnce(map, "idle", configure);

});

function go_to_me(){
    if(navigator.geolocation){
        navigator.geolocation.getCurrentPosition(function(position){
            var mycurrentLat = position.coords.latitude;
            var mycurrentLong = position.coords.longitude;
            myposition = new google.maps.LatLng(mycurrentLat, mycurrentLong);
            map.setCenter(myposition);
        });
    }
}

/**
 * Adds marker for place to map.
 */
function addMarker(place)
{
    // TODO
    var lat = place["latitude"];
    var lon = place["longitude"];
    var markerLatLong = new google.maps.LatLng(lat, lon);
    var label = place["place_name"] + ", " + place["admin_name1"];
    var icon = "img/icon.png";

    var listItems = [];

    marker = new MarkerWithLabel({
        position: markerLatLong,
        icon: icon,
        map: map,
        draggable: false,
        labelContent: label,
        labelAnchor: new google.maps.Point(-18, 24),
        labelInBackground: false
    });

    markers.push(marker);

    var parameter = "geo="+ place["postal_code"];

    // Create an info window
    marker.info = new google.maps.InfoWindow({
        // Set up the ajax loader gif
        content: "<div id='articles'><img id='loader' src='img/ajax-loader.gif' /></div>"
    });

    // Add a click listener that will load the articles using ajax.
    google.maps.event.addListener(marker, "click", function (e){ 
        
        marker.info.open(map, this);
        // Technique adapted from Baer at this link: http://stackoverflow.com/questions/9760328/clearest-way-to-build-html-elements-in-jquery
        var html = ["<ul>"];
        // Modify the html and load-in the articles
        $.getJSON("articles.php", parameter).done(function(data){
            $.each(data, function(i, item){
                html.push("<li><a href='"+item.link+"' target='_blank'>"+item.title+"</a></li>");
            });
            html.push("</ul>");
            marker.info.setContent(html.join("\n"));
        }).fail(function(jqXHR, textStatus, errorThrown){
            console.log(errorThrown.toString());
        });
    });
}

/**
 * Configures application.
 */
function configure()
{
    // update UI after map has been dragged
    google.maps.event.addListener(map, "dragend", function() {
        update();
    });

    // update UI after zoom level changes
    google.maps.event.addListener(map, "zoom_changed", function() {
        update();
    });

    // remove markers whilst dragging
    google.maps.event.addListener(map, "dragstart", function() {
        removeMarkers();
    });

    // configure typeahead
    // https://github.com/twitter/typeahead.js/blob/master/doc/jquery_typeahead.md
    $("#q").typeahead({
        autoselect: true,
        highlight: true,
        minLength: 1
    },
    {
        source: search,
        templates: {
            empty: "no places found yet",
            suggestion: function(data) {
                return "<p>" + data.place_name + ", " + data.admin_name1 +  " " + data.postal_code + "</p>"
            } 
        }
    });

    // re-center map after place is selected from drop-down
    $("#q").on("typeahead:selected", function(eventObject, suggestion, name) {

        // ensure coordinates are numbers
        var latitude = (_.isNumber(suggestion.latitude)) ? suggestion.latitude : parseFloat(suggestion.latitude);
        var longitude = (_.isNumber(suggestion.longitude)) ? suggestion.longitude : parseFloat(suggestion.longitude);

        // set map's center
        map.setCenter({lat: latitude, lng: longitude});

        // update UI
        update();
    });

    // hide info window when text box has focus
    $("#q").focus(function(eventData) {
        hideInfo();
    });

    // re-enable ctrl- and right-clicking (and thus Inspect Element) on Google Map
    // https://chrome.google.com/webstore/detail/allow-right-click/hompjdfbfmmmgflfjdlnkohcplmboaeo?hl=en
    document.addEventListener("contextmenu", function(event) {
        event.returnValue = true; 
        event.stopPropagation && event.stopPropagation(); 
        event.cancelBubble && event.cancelBubble();
    }, true);

    // update UI
    update();

    // give focus to text box
    $("#q").focus();
}

/**
 * Hides info window.
 */
function hideInfo()
{
    info.close();
}

/**
 * Removes markers from map.
 */
function removeMarkers()
{
    _.each(markers, function(marker){
        marker.setMap(null);
    });

}

/**
 * Searches database for typeahead's suggestions.
 */
function search(query, cb)
{
    // get places matching query (asynchronously)
    var parameters = {
        geo: query
    };
    $.getJSON("search.php", parameters)
    .done(function(data, textStatus, jqXHR) {

        // call typeahead's callback with search results (i.e., places)
        cb(data);
    })
    .fail(function(jqXHR, textStatus, errorThrown) {

        // log error to browser's console
        console.log(errorThrown.toString());
    });
}

/**
 * Shows info window at marker with content.
 */
function showInfo(marker, content)
{
    // start div
    var div = "<div id='info'>";
    if (typeof(content) === "undefined")
    {
        // http://www.ajaxload.info/
        div += "<img alt='loading' src='img/ajax-loader.gif'/>";
    }
    else
    {
        div += content;
    }

    // end div
    div += "</div>";

    // set info window's content
    info.setContent(div);

    // open info window (if not already open)
    info.open(map, marker);
}

/**
 * Updates UI's markers.
 */
function update() 
{
    // get map's bounds
    var bounds = map.getBounds();
    var ne = bounds.getNorthEast();
    var sw = bounds.getSouthWest();

    // get places within bounds (asynchronously)
    var parameters = {
        ne: ne.lat() + "," + ne.lng(),
        q: $("#q").val(),
        sw: sw.lat() + "," + sw.lng()
    };
    $.getJSON("update.php", parameters)
    .done(function(data, textStatus, jqXHR) {

        // remove old markers from map
        removeMarkers();

        // add new markers to map
        for (var i = 0; i < data.length; i++)
        {
            addMarker(data[i]);
        }
     })
     .fail(function(jqXHR, textStatus, errorThrown) {

         // log error to browser's console
         console.log(errorThrown.toString());
     });
};