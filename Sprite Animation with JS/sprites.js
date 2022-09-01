const canvas = document.getElementById("canvas");
const context = canvas.getContext("2d");
canvas.width = 256;
canvas.height = 256;

const pressedKeys = []
const sprite = new Image();
sprite.src = "Charrunning.png";
const frameWidth = 16;
const frameHeight = 16;

let frame = 2;
stopping = false;
sliding = false;
function animate(){
    context.clearRect(0,0,canvas.width,canvas.height);
    context.imageSmoothingEnabled = false;
    context.drawImage(sprite, frame*frameWidth, 0, frameWidth, frameHeight,0,0,canvas.width,canvas.height);
    //requestAnimationFrame(animate);
    if(0 <= frame && frame < 13 && !stopping){frame++;}
    else if(frame == 13){frame = 2;} 
    else if(stopping && frame >1){frame = 1;} 
    else if (stopping && frame ==1){frame = 0;}
    if(14 <= frame && frame < 17 && sliding){frame++;}
    
}

setInterval(function(){
    animate();
    getInput();
    document.getElementById("frame").innerHTML= frame;
},100)


window.addEventListener("keydown", function(e){
    pressedKeys[e.key] = true;
}
);

window.addEventListener("keyup", function(e){
    pressedKeys[e.key] = false;
}
);

function getInput(){
    if(pressedKeys["w"] ^ pressedKeys["W"]){
        document.getElementById("key-W").style.backgroundColor = "red";
    }else{
        document.getElementById("key-W").style.backgroundColor = "transparent";
    }
    if(pressedKeys["a"] ^ pressedKeys["A"]){
        document.getElementById("key-A").style.backgroundColor = "red";
        stopping = true;
    }else{
        document.getElementById("key-A").style.backgroundColor = "transparent";
        stopping = false;
    }
    if(pressedKeys["s"] ^ pressedKeys["S"]){
        document.getElementById("key-S").style.backgroundColor = "red";
        if(frame < 14){frame = 14;}
        sliding = true;
    }else{
        document.getElementById("key-S").style.backgroundColor = "transparent";
        sliding = false
        if(14 <= frame){frame--;}
    }
    if(pressedKeys["d"] ^ pressedKeys["D"]){
        document.getElementById("key-D").style.backgroundColor = "red";
    }else{
        document.getElementById("key-D").style.backgroundColor = "transparent";
    }
}