//alert("JS Works !");
//console.log("!!!!!!!!!!!!!!!!!!!!!!!!!!! BONJOUR TOUT LE MONDE ! !!!!!!!!!!!!!!!!!!!!!");
function showBA()
{
	var ba = document.getElementById("ba_hover");
	ba.style.display = "block";
	return false;
}
function hideBA()
{
	var ba = document.getElementById("ba_hover");
	ba.style.display = "none";
	toggleVideo('hide');
	return false;
}
function toggleVideo(state) {
    // if state == 'hide', hide. Else: show video
    var div = document.getElementById("ba");
    var iframe = div.getElementsByTagName("iframe")[0].contentWindow;
    //div.style.display = state == 'hide' ? 'none' : '';
    func = state == 'hide' ? 'pauseVideo' : 'playVideo';
    iframe.postMessage('{"event":"command","func":"' + func + '","args":""}', '*');
}
