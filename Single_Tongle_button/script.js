var firebaseConfig = {
    apiKey: "AIzaSyD4r9IZ4nDeFWVTv4W52nB_13l1YC6d7fc",
    authDomain: "toggle-button-3d8fe.firebaseapp.com",
    databaseURL: "https://toggle-button-3d8fe-default-rtdb.firebaseio.com",
    projectId: "toggle-button-3d8fe",
    storageBucket: "toggle-button-3d8fe.appspot.com",
    messagingSenderId: "807063547069",
    appId: "1:807063547069:web:0ca44bccf198b408de1bd4",
    measurementId: "G-7Q81S5145B"
  };
  // Initialize Firebase
  firebase.initializeApp(firebaseConfig);

$(document).ready(function(){
    var database = firebase.database();
	var Led1Status;

	database.ref().on("value", function(snap){
		Led1Status = snap.val().Led1Status;
		if(Led1Status == "1"){    // check from the firebase
			//$(".Light1Status").text("The light is off");
			document.getElementById("unact").style.display = "none";
			document.getElementById("act").style.display = "block";
		} else {
			//$(".Light1Status").text("The light is on");
			document.getElementById("unact").style.display = "block";
			document.getElementById("act").style.display = "none";
		}
	});

    $(".toggle-btn").click(function(){
		var firebaseRef = firebase.database().ref().child("Led1Status");

		if(Led1Status == "1"){    // post to firebase
			firebaseRef.set("0");
			Led1Status = "0";
		} else {
			firebaseRef.set("1");
			Led1Status = "1";
		}
	})
});