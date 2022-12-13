#include <SDL2/SDL.h>
#include <unistd.h>
#include "function.h"

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 600
#define FPS 240

int longeurPad = 20;
int hauteurPad = 200;
int speedPadY = 20;

int drawPaddelDroit();
int posPadDroX = 50;
int posPadDroY = 200;

int drawPaddelGauche();
int posPadGauX = 930;
int posPadGauY = 200;

int drawLigne();

int drawBalle();
int posBallX = 500;
int posBallY = 300;
int rayon = 10;
int speedBallX ;
int speedBallY ;

int colilionMur();
int colisionPadGauche();
int colisionPadDroit();

int scoreDroit();
int pointDroit = 0;

int scoreGauche();
int pointGauche = 0;

int afficheScoreDroit();
int afficheScoreGauche();

int nouvelPartie();

int fond();

void drawGame(){
    /* Ici je dessine mon jeu
     * exemple position x, y modifiés dans KeyPressed() et utilisés pour
     * pouvoir deplacer la figure à chaque boucle de gameLoop()
     */
    clear();
    
    fond();
    drawPaddelDroit();
    drawPaddelGauche();
    drawLigne();
    drawBalle();
    colilionMur();
    colisionPadGauche();
    colisionPadDroit();
    scoreDroit();
    scoreGauche();
    afficheScoreGauche();
    afficheScoreDroit();
    nouvelPartie();
    
    actualize();
    usleep(1000000 / FPS); // 60 images par seconde | 1000000 = 1 seconde
}
void KeyPressed(SDL_Keycode touche){
    /** @brief event.key.keysym.sym renvoi la touche appuyé
     *
     */
    switch (touche) {
        // Voir doc SDL_Keycode pour plus de touches https://wiki.libsdl.org/SDL_Keycode
        // ici exemple ou appuyer sur les touches Q | D modifie x (position du carré dans drawGame())
        case SDLK_q:
            //touche q appuyé
            printf("Q\n");
            if(posPadDroY > 20)
                posPadDroY = posPadDroY - speedPadY;
            break;

        case SDLK_d:
            //touche d appuyé
            printf("D\n");
            if(posPadDroY <= 360)
                posPadDroY = posPadDroY + speedPadY;
            break;

        case SDLK_k:
            //touche k appuyé
            printf("K\n");
            if(posPadGauY > 20)
                posPadGauY = posPadGauY - speedPadY;
            break;

        case SDLK_m:
            //touche m appuyé
            printf("M\n");
            if(posPadGauY <= 360 )
                posPadGauY = posPadGauY + speedPadY;
            break;

        case SDLK_SPACE:
            // touche espace appuyé
            printf("Espace\n");

            if (pointGauche%2 == 0)
            {
                speedBallX = -2;
                speedBallY = 0;
            }
            else
            {
                speedBallX = 2;
                speedBallY = 0;
            }

            if (pointGauche == 5 || pointDroit == 5)
            {
                pointDroit = 0;
                pointGauche= 0;
            }
            break;

        case SDLK_ESCAPE:
            freeAndTerminate();
            break;
        default:
            break;
    }
}
void joyButtonPressed(){
}

void gameLoop() {
    int programLaunched = 1;
    while (programLaunched == 1) {
        // Boucle pour garder le programme ouvert
        // lorsque programLaunched est different de 1
        // on sort de la boucle, donc de la fonction
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            // boucle pour la gestion d'évenement
            switch (event.type) {
                /** event.type renvoi le type d'evenement qui se passe
                 * (si on appuie sur une touche, clique de souris...)
                 * en fonction du type d'évènement on à alors
                 * différentes information accessibles
                 * voir doc pour plus d'event https://wiki.libsdl.org/SDL_EventType
                 */
                case SDL_QUIT:
                    // quand on clique sur fermer la fénêtre en haut à droite
                    programLaunched = 0;
                    break;
                case SDL_MOUSEBUTTONUP:
                    /* clique de la souris
                     * event.motion.y | event.motion.x pour les positions de la souris
                     */
                    printf("position de la souris x : %d , y : %d\n", event.motion.x, event.motion.y);
                    break;
                case SDL_KEYDOWN:
                    KeyPressed(event.key.keysym.sym);
                    break;
                case SDL_JOYBUTTONDOWN:
                    break;
                default:
                    break;
            }
        }
        /* coder ici pour que le code s'execute après chaque évenement
         * exemple dessiner un carré avec position int x, int y qu'on peut
         * deplacer lorsqu'on appuie sur une touche
         */
        drawGame();
    }
}

int main(){
    /** @description 3 fonctions dans le main qui permettent de créer l'application et la maintenir ouverte :
     *  init(...) : initialiser la SDL/ fenêtre
     *  gameLoop() : boucle de jeu dans laquelle l'application reste ouverte
     *  freeAndTerminate() : quitte le programme proprement
     */
    init(WINDOW_WIDTH, WINDOW_HEIGHT);
    gameLoop();
    printf("Fin du programme\n");
    freeAndTerminate();
}

int drawPaddelGauche()
{
    changeColor(255,20,20);
    drawRect(posPadGauX, posPadGauY, longeurPad, hauteurPad);
}

int drawPaddelDroit()
{
    changeColor(20,20,255);
    drawRect(posPadDroX, posPadDroY, longeurPad, hauteurPad);
 
}

int drawLigne()
{
    changeColor(255,255,255);
    drawRect(497.5, 10, 5, 580);
}

int drawBalle()
{
    posBallX = posBallX + speedBallX;
    posBallY = posBallY + speedBallY;

    changeColor(255, 155, 55);
    drawCircle(posBallX, posBallY, rayon);
}

int colilionMur()
{
    drawBalle();

    if( (posBallY + speedBallY < rayon) || posBallY + speedBallY + rayon > 600)
    {
        speedBallY = -speedBallY;
    }
}

int colisionPadGauche()
{
    if( posBallY + rayon >= posPadGauY &&
        posBallY - rayon <= posPadGauY + hauteurPad &&
        posBallX + rayon >= posPadGauX &&
        posBallX - rayon <= posPadGauX + longeurPad)
    {
        if(posPadGauY <= posBallY || posBallY >= posPadGauY + 95)
        {
            speedBallY = -2;
            speedBallX = -2;
                
        }
            
        if(posPadGauY + 96 <= posBallY || posBallY >= posPadGauY + 104)
        {
           
            speedBallY =  0;
            speedBallX = -2; 
                
        }
            
        if(posPadGauY + 105 <= posBallY || posBallY >= posPadGauY + 200)
        {
            
            speedBallY =  2;
            speedBallX = -2;
                
        }
                
            
    }
}

int colisionPadDroit()
{
    if( posBallY + rayon >= posPadDroY &&
        posBallY - rayon <= posPadDroY + hauteurPad &&
        posBallX + rayon >= posPadDroX &&
        posBallX - rayon <= posPadDroX + longeurPad)
    {
        if(posPadDroY <= posBallY || posBallY >= posPadDroY + 95)
        {
            speedBallY = -2;
            speedBallX =  2;
                
        }
            
        if(posPadDroY + 96 <= posBallY || posBallY >= posPadDroY + 104)
        {
           
            speedBallY =  0;
            speedBallX =  2; 
                
        }
            
        if(posPadDroY + 105 <= posBallY || posBallY >= posPadDroY + 200)
        {
            
            speedBallY = -2;
            speedBallX =  2;
                
        }
                
            
    }
}

int scoreGauche()
{
    if (posBallX + rayon >= 1000)
    {
        pointDroit++;
        posBallX = 500;
        posBallY = 300;
        speedBallX = 0;
        speedBallY = 0;
    }
}

int scoreDroit()
{
    if (posBallX + rayon <= 0)
    {
        pointGauche++;
        posBallX = 500;
        posBallY = 300;
        speedBallX = 0;
        speedBallY = 0;
    }
}

int afficheScoreGauche()
{
    printf("score gauche: %d\n",pointGauche );

    if (pointGauche == 1)
    {
        changeColor(255,20,20);
        drawCircle(530,30,5);
    }
    if (pointGauche == 2)
    {
        changeColor(255,20,20);
        drawCircle(560,30,5);
        drawCircle(530,30,5);
    }
    if (pointGauche == 3)
    {
        changeColor(255,20,20);
        drawCircle(560,30,5);
        drawCircle(530,30,5);
        drawCircle(590,30,5);
    }
    if (pointGauche == 4)
    {
        changeColor(255,20,20);
        drawCircle(560,30,5);
        drawCircle(530,30,5);
        drawCircle(590,30,5);
        drawCircle(620,30,5);
    }
    if (pointGauche == 5)
    {
        changeColor(255,20,20);
        drawCircle(560,30,5);
        drawCircle(530,30,5);
        drawCircle(590,30,5);
        drawCircle(620,30,5);
        drawCircle(650,30,5);
        sprite(550,150,"image/win.bmp");
    }
}

int afficheScoreDroit()
{
    printf("score droit: %d\n",pointDroit );

    if (pointDroit == 1)
    {
        changeColor(20,20,255);
        drawCircle(470,30,5);
    }
    if (pointDroit == 2)
    {
        changeColor(20,20,255);
        drawCircle(470,30,5);
        drawCircle(440,30,5);
    }
    if (pointDroit == 3)
    {
        changeColor(20,20,255);
        drawCircle(470,30,5);
        drawCircle(440,30,5);
        drawCircle(410,30,5);
    }
    if (pointDroit == 4)
    {
        changeColor(20,20,255);
        drawCircle(470,30,5);
        drawCircle(440,30,5);
        drawCircle(410,30,5);
        drawCircle(380,30,5);
    }
    if (pointDroit == 5)
    {
        changeColor(20,20,255);
        drawCircle(470,30,5);
        drawCircle(440,30,5);
        drawCircle(410,30,5);
        drawCircle(380,30,5);
        drawCircle(350,30,5);
        sprite(100,150,"image/win.bmp");

    }
}

int nouvelPartie()
{
    if(pointDroit == 5 || pointGauche == 5)
    {
        printf("nouvel parie appuier sur A\n");
    }
}

int fond()
{
    changeColor(255,255,255);
    drawRect(20,0,960,600);
    changeColor(0,0,0);
    drawRect(25,5,950,590);
    changeColor(255,255,255);
    drawCircle(500,300,100);
    changeColor(0,0,0);
    drawCircle(500,300,95);
}