for(var i = 1; i < document.getElementsByTagName("input").length; i++){
	var inputid = document.getElementsByTagName("input")[i].id;
    if(inputid.substring(0,4) == "answ"){
		if(inputid.trim().length > 6){
			var xzth = new Array()
			xzth = inputid.split("&");
            if(xzth[2] == "1"){
				if(xzth[3] == "1"){
					document.getElementById(inputid).checked = true;
                }
            }
        }
    }
    if(inputid.substring(0,3) == "sub"){
		if(inputid.trim().length > 6){
			var subxzth = new Array()
			subxzth = inputid.split("&");
            if(subxzth[1] == "1"){
				document.getElementById(inputid).value = 1;
            }
        }
    }
}
