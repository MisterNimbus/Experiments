const canvas = document.getElementById("canvas");
const context = canvas.getContext("2d");

canvas.height = 512;
canvas.width = 1024;

const spriteWidth = 16;
const pixelWidth = 4;
const charSprite = new Image();
charSprite.src = "Charrunning.png";

const tileSprite = new Image();
tileSprite.src = "TilesNew.png";

class player{
    constructor(x,y){
        this.x = x;
        this.y = y;
        this.vel_x = 0;
        this.vel_y = 0;
        this.frame = 0;
        this.sliding = false;
        this.standing = true;
        this.smoothnessCounter = 0;
    }
    getInput(){
    if(pressedKeys["w"] ^ pressedKeys["W"]){
    }else{
    }
    if(pressedKeys["a"] ^ pressedKeys["A"]){
        this.standing = true;
    }else{
        this.standing = false;
    }
    if(pressedKeys["s"] ^ pressedKeys["S"]){
        if(this.frame < 14){this.frame = 14;}
        this.sliding = true;
    }else{
        this.sliding = false
        if(14 <= this.frame){this.frame--;}
    }
    if(pressedKeys["d"] ^ pressedKeys["D"]){
    }else{
    }
    }
    update(){
        this.x += this.vel_x;
        this.smoothnessCounter++;
        context.imageSmoothingEnabled = false;
        context.drawImage(charSprite, this.frame*spriteWidth, 0, 16, 16,this.x,this.y,64,64);
        if(this.x > canvas.width - spriteWidth*pixelWidth){
            context.drawImage(charSprite, this.frame*spriteWidth, 0, 16, 16,this.x - canvas.width,this.y,64,64);
        }
        if(this.x > canvas.width){this.x -= canvas.width;}
        if(this.smoothnessCounter == pixelWidth){
        this.getInput();
        if(0 <= this.frame && this.frame < 13 && !this.standing){
            this.frame++; 
            if(this.vel_x == 0){
                this.vel_x=1
            }
            else if(this.vel_x<4){
                this.vel_x*=2;}
            if(this.vel_x > 4){
                this.vel_x *= 0.9;
            }
            }
        else if(this.frame == 13){this.frame = 2;} 
        else if(this.standing && this.frame >1){this.frame = 1; this.vel_x/=2} 
        else if (this.standing && this.frame ==1){this.frame = 0; this.vel_x=0;}
        if(14 <= this.frame && this.frame < 17 && this.sliding){this.frame++; this.vel_x*=0.9;}
        if(this.frame == 17){this.vel_x*=0.8;}
        this.smoothnessCounter = 0;
        }
    }
}

class game{
    constructor()
    {
        this.gameObjects = [];
        this.platformContents = [
            [[0,0],[0,1],[0,0],[1,2],[1,1],[0,1],[0,0],[1,3],[0,0],[1,0],[0,2],[0,1],[0,3],[0,2],[1,1],[1,2]],
            [[0,0],[1,0],[0,2],[0,1],[0,3],[0,2],[1,1],[1,2],[0,0],[1,2],[1,1],[0,1],[0,0],[1,3],[0,0],[0,3]]];
    }
    addGameObject(gameObject){
        this.gameObjects.push(gameObject);
    }
    updatePlatform(){
        context.imageSmoothingEnabled = false;
        for(let j = 0; j < this.platformContents.length; j++){
            for(let i = 0; i < this.platformContents[0].length; i++){
                context.drawImage(tileSprite, this.platformContents[j][i][0]*spriteWidth, this.platformContents[j][i][1]*spriteWidth, 16, 16,i*64,384+j*64,64,64);
            }
        }
    }
    updateBackground(){

    }
    update()
    {
        
        //updateBackground();
        this.updatePlatform();
        this.gameObjects.forEach(gameObject => {
            gameObject.update();
        });
    }
}

const mainChar = new player(512,256+64);
const gameClass = new game()

gameClass.addGameObject(mainChar);

setInterval(function(){
    context.clearRect(0,0,canvas.width,canvas.height);
    gameClass.update();
    //mainChar.update();
}, 25)

const terrain = [[0,0],[0,1],[0,0],[0,1],[0,1],[0,1],[0,1],[0,2],[1,1],[0,1],[0,1]]

const pressedKeys = []

window.addEventListener("keydown", function(e){
    pressedKeys[e.key] = true;
}
);

window.addEventListener("keyup", function(e){
    pressedKeys[e.key] = false;
}
);
