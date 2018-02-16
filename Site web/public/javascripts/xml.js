$( document ).ready( function(){
	var xml = new XMLHttpRequest();
	xml.onreadystatechange = function(event) {
		// XMLHttpRequest.DONE === 4
		if (this.readyState === XMLHttpRequest.DONE) {
			if (this.status === 200) {
				var xmlData=xml.responseXML;
				
				xmlData=(new DOMParser()).parseFromString(xml.responseText,'text/xml');
			var profile=xmlData.getElementsByTagName("profile");
	var profiles=xmlData.getElementsByTagName("profiles");

document.body.style.background = "Azure      url('http://i.ebayimg.com/thumbs/images/g/F3oAAOSw~oFXNQQp/s-l225.jpg' )  ";
 var div = document.createElement("DIV");
 div.setAttribute("class","w3-container w3-teal");
 document.body.appendChild(div);
 var h1 = document.createElement("H1");
 var t5 = document.createTextNode(" Voici les profils des utilisateurs : ");
  h1.appendChild(t5)
 //div2.setAttribute("class","panel-heading");
 div.appendChild(h1);
 

 for( var index = 0; index < profiles[0].getElementsByTagName("profile").length ; index++ ) {

 var table1 = document.createElement("TABLE");
 document.body.appendChild(table1);
 
 var TH = document.createElement("TR");
 table1.appendChild(TH);
 var tr = document.createElement("TD");
 TH.appendChild(tr);
 

 
 
	/*pour la figure*/
	var x = document.createElement("FIGURE");
    //x.setAttribute("id", "myFigure");
	x.setAttribute ("class", "snip1336");
	 tr.appendChild(x);
	
	if (xmlData.getElementsByTagName("profile")[index].getElementsByTagName("image").length > 0) 
	{
		var y = document.createElement("IMG");
		y.setAttribute("src", "Exe/" + xmlData.getElementsByTagName("profile")[index].getElementsByTagName("image")[0].firstChild.data);
		y.setAttribute("alt", "sample87");
		x.appendChild(y);
	}
	var Z = document.createElement("FIGCAPTION");
	var Z1 = document.createElement("IMG");
  
	x.appendChild(Z);
	Z.appendChild(Z1);
	
	if (xmlData.getElementsByTagName("profile")[index].getElementsByTagName("firstName").length >0)
	{	
		var h2 = document.createElement("H2");
		h2.setAttribute("class","glyphicon glyphicon-user");
		var t = document.createTextNode(xmlData.getElementsByTagName("profile")[index].getElementsByTagName("firstName")[0].firstChild.data);
	
		h2.appendChild(t);
		Z.appendChild(h2);
	}
	
	
	
	
	var p = document.createElement("P");
	
	var tp = document.createTextNode("Information de l'utilisateur:");
	
	p.appendChild(tp);
	Z.appendChild(p);
	
	
	if (xmlData.getElementsByTagName("profile")[index].getElementsByTagName("username").length >0)
	{	
	var id = document.createElement("P");
	id.setAttribute("class","glyphicon glyphicon-user");
	var idt = document.createTextNode("ID:    "+xmlData.getElementsByTagName("profile")[index].getElementsByTagName("username")[0].firstChild.data);	
	id.appendChild(idt);
	Z.appendChild(id);
	}
	
	var br1 = document.createElement("BR");
	Z.appendChild(br1);
	
	if (xmlData.getElementsByTagName("profile")[index].getElementsByTagName("lastName").length >0)
	{	
		var prenom = document.createElement("P");
		prenom.setAttribute("class","glyphicon glyphicon-user");
		var prenomt = document.createTextNode( "Nom:    "+xmlData.getElementsByTagName("profile")[index].getElementsByTagName("lastName")[0].firstChild.data);
	
		prenom.appendChild(prenomt);
		Z.appendChild(prenom);
	}
	
	var br5 = document.createElement("BR");
	Z.appendChild(br5);
	
	if (xmlData.getElementsByTagName("profile")[index].getElementsByTagName("email").length > 0)
		{
			var email = document.createElement("P");
			email.setAttribute("class","glyphicon glyphicon-envelope");
			var emailt = document.createTextNode("email:    "+xmlData.getElementsByTagName("profile")[index].getElementsByTagName("email")[0].firstChild.data);
			email.appendChild(emailt);
			Z.appendChild(email);
		}
		
		
	if (xmlData.getElementsByTagName("profile")[index].getElementsByTagName("isAdmin").length >0)
	{	
		var isAdmin = document.createElement("P");
		isAdmin.setAttribute("class","glyphicon glyphicon-eye-open");
		var isAdmint ;
		if (xmlData.getElementsByTagName("profile")[index].getElementsByTagName("isAdmin")[0].firstChild.data == "true")
		{
	
			isAdmint = document.createTextNode("Admin");
		}
		else
		{
			isAdmint = document.createTextNode("Utilisateur simple");
	
		}
	
		isAdmin.appendChild(isAdmint);
		Z.appendChild(isAdmin);
	}
	
	var p2 = document.createElement("P");
	var tp2 = document.createTextNode("Statistiques des utilisations:");
	p2.appendChild(tp2);
	Z.appendChild(p2);
	
/*	var cmod = document.createElement("P");
	cmod.setAttribute("class","	glyphicon glyphicon-picture");

	var text = "Cartes cr\351\351es:   "  ;
	
	for ( var ii = 0; ii < profile[index].getElementsByTagName("Creation")[0].getElementsByTagName("card").length   ; ii++) {
  
console.log("ssssssssssssssss");

text += profile[index].getElementsByTagName("Creation")[0].getElementsByTagName("card")[ii].firstChild.data + "/";

}	
	var cmodt = document.createTextNode(text);
	cmod.appendChild(cmodt);
	Z.appendChild(cmod);
	
	
	var ccre = document.createElement("P");
	ccre.setAttribute("class","	glyphicon glyphicon-pencil");
	var text2 = "Cartes modifi\351es :   ";
	for ( var jj = 0; jj < profile[index].getElementsByTagName("modification")[0].getElementsByTagName("card").length   ; jj++) {
  


text2 += profile[index].getElementsByTagName("modification")[0].getElementsByTagName("card")[jj].firstChild.data + "/";

}	
	var ccret = document.createTextNode(text2);
	ccre.appendChild(ccret);
	Z.appendChild(ccre);
	
*/
	
    }  
 
 
				
			}
		} else {
			console.log("Status de la réponse: %d (%s)", this.status, this.statusText);
		}
	}
	xml.open ('GET','profiles',false);
	xml.send(null);


var xml = new XMLHttpRequest();
	xml.onreadystatechange = function(event) {
		// XMLHttpRequest.DONE === 4
		if (this.readyState === XMLHttpRequest.DONE) {
			if (this.status === 200) {
				var xmlData=xml.responseXML;
				
				xmlData=(new DOMParser()).parseFromString(xml.responseText,'text/xml');
				var card=xmlData.getElementsByTagName("card");
	var cards=xmlData.getElementsByTagName("cards");
	
	
 
var div = document.createElement("DIV");
 div.setAttribute("class","w3-container w3-teal");
 document.body.appendChild(div);
 var h1 = document.createElement("H1");
 var t5 = document.createTextNode(" Voici les informations sur les cartes : ");
  h1.appendChild(t5)
 //div2.setAttribute("class","panel-heading");
 div.appendChild(h1);
 
 
	
for( var index = 0; index < cards[0].getElementsByTagName("card").length ; index++ ) {
 /*var table = document.createElement("TABLE");
 document.body.appendChild(table);*/
  var table1 = document.createElement("TABLE");
 document.body.appendChild(table1);
 
 var tr = document.createElement("TR");
 table1.appendChild(tr);
/* var tr = document.createElement("H2");
 table.appendChild(tr);*/
 
	/*pour la figure*/
	var x = document.createElement("FIGURE");
    //x.setAttribute("id", "myFigure");
	x.setAttribute ("class", "snip1336");
	tr.appendChild(x);
	
	 
	var y = document.createElement("IMG");
    y.setAttribute("src", "https://encrypted-tbn1.gstatic.com/images?q=tbn:ANd9GcRhnBestaEcrx2kf-pE1oNrsrVP5prJTe3i_Yu-VD9lXPnwnxBI");
    //y.setAttribute("width", "304");
    //y.setAttribute("width", "228");
    y.setAttribute("alt", "sample87");

    x.appendChild(y);
	var Z = document.createElement("FIGCAPTION");
	var Z1 = document.createElement("IMG");
  ;
	x.appendChild(Z);
	Z.appendChild(Z1);
	
	
	if (xmlData.getElementsByTagName("card")[index].getElementsByTagName("name").length >0)
	{
		var h2 = document.createElement("H2");
		h2.setAttribute("class","glyphicon glyphicon-picture");
		var t = document.createTextNode(xmlData.getElementsByTagName("card")[index].getElementsByTagName("name")[0].firstChild.data);
	
		h2.appendChild(t);
		Z.appendChild(h2);
	}
	
	
	
	var p = document.createElement("P");
	//p.setAttribute("class","thick")
	var tp = document.createTextNode("Information de l'utilisateur:");
	
	p.appendChild(tp);
	Z.appendChild(p);
	
	
	if (xmlData.getElementsByTagName("card")[index].getElementsByTagName("isPrivate").length >0)
	{
		var isPrivate = document.createElement("P");
		isPrivate.setAttribute("class","glyphicon glyphicon-user");
		var isPrivatet ;
		if (xmlData.getElementsByTagName("card")[index].getElementsByTagName("isPrivate")[0].firstChild.data == "true")
		{
	
			isPrivatet = document.createTextNode("Priv\351e");
		}
		else
		{
			isPrivatet = document.createTextNode("Publique");
		}
	
		isPrivate.appendChild(isPrivatet);
		Z.appendChild(isPrivate);
	}
	
	var br = document.createElement("BR");
	Z.appendChild(br);
	
	
	
	
	if (xmlData.getElementsByTagName("card")[index].getElementsByTagName("score").length >0)
	{
		var score = document.createElement("P");
		score.setAttribute("class","glyphicon glyphicon-envelope");
		var scoret = document.createTextNode("score:    "+xmlData.getElementsByTagName("card")[index].getElementsByTagName("score")[0].firstChild.data);
		score.appendChild(scoret);
		Z.appendChild(score);
	}
		var br2 = document.createElement("BR");
		Z.appendChild(br2);
	
	
	if (xmlData.getElementsByTagName("card")[index].getElementsByTagName("votes").length >0)
	{
		var vote = document.createElement("P");
		vote.setAttribute("class","glyphicon glyphicon-envelope");
		var votet = document.createTextNode("vote:    "+xmlData.getElementsByTagName("card")[index].getElementsByTagName("votes")[0].firstChild.data);
		vote.appendChild(votet);
		Z.appendChild(vote);
	}
	
	var br3 = document.createElement("BR");
	Z.appendChild(br3);
	var createur = document.createElement("P");
	
	if (xmlData.getElementsByTagName("card")[index].getElementsByTagName("creator").length >0)
	{
		createur.setAttribute("class","glyphicon glyphicon-user");
		var createurt = document.createTextNode("cr\351ateur:    "+xmlData.getElementsByTagName("card")[index].getElementsByTagName("creator")[0].firstChild.data);
		createur.appendChild(createurt);
		Z.appendChild(createur);
	}
	
	var br4 = document.createElement("BR");
	Z.appendChild(br4);
	
	
	
	
	
	if (xmlData.getElementsByTagName("card")[index].getElementsByTagName("modifiers").length >0)
	{
		var mod = document.createElement("P");
		mod.setAttribute("class","	glyphicon glyphicon-picture");

		var text = "modificateur:   "  ;
		if (xmlData.getElementsByTagName("card")[index].getElementsByTagName("modifiers")[0].getElementsByTagName("user").length >0)
	
		{
			for ( var ii = 0; ii < xmlData.getElementsByTagName("card")[index].getElementsByTagName("modifiers")[0].getElementsByTagName("user").length   ; ii++) {
  
			text += xmlData.getElementsByTagName("card")[index].getElementsByTagName("modifiers")[0].getElementsByTagName("user")[ii].firstChild.data + "/";

			}
		}
	
			var modt = document.createTextNode(text);
			mod.appendChild(modt);
			Z.appendChild(mod);
		
	}
	
	}
			
			
			
			
			}
		} else {
			console.log("Status de la réponse: %d (%s)", this.status, this.statusText);
		}
	}
	xml.open ('GET','cards',false);
	xml.send(null);
});