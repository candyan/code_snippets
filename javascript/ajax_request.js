function ajax_request(argument)
{
    var aj = new XMLHttpRequest();
    aj.onreadystatechange = function() {
        if (aj.readyState == 4 && aj.status == 200)
            // do something to the page
    };
    
    aj.open("GET", /* URL */, true);
    aj.send();
}
