let menu = document.getElementById("click-menu");
let nav2=document.getElementsByClassName("nav-2");

function press(){
    let secondNav = document.getElementById("second-nav");
    if(secondNav.style.display==="none"){
    secondNav.style.display="block";
    secondNav.style.display="flex";
    secondNav.style.flexDirection="column";
    secondNav.style.justifyContent="flex-start";
    secondNav.style.paddingTop="58px";
    secondNav.style.backgroundColor="black";
    secondNav.style.color = "white"
    nav2.style.display="flex";
    nav2.style.flexDirection="column";
    }else{
        secondNav.style.display="none";
    }
}