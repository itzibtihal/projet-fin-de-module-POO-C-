#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <vector>
#include<SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
using namespace sf;
using namespace std;
class Fruit{
    private :
        RectangleShape apple;
        Vector2f fposition;

    public :
        Fruit(){
            apple.setSize(Vector2f(50,50));
            apple.setFillColor(Color::Red);


        }

        void moveFruit(){
            setfposition(rand()%1150,rand()%500+150); // y : entre 150 et 650
            apple.setPosition(fposition);    }

        //getters setters
        Vector2f getfposition(){
            return fposition;  }
        RectangleShape getFruit(){
            return apple;         } // need it to draw the fruit
        void setfposition(int x,int y){
            fposition.x=x;
            fposition.y=y;
        }

};

class Obstacle{
    private :
        RectangleShape obstacles;
        Vector2f Oposition;

    public :
        Obstacle(){
            //RectangleShape rectangle(sf::Vector2f(128.0f,128.0f));
            obstacles.setSize(Vector2f(20.0f,128.0f));
            obstacles.setFillColor(Color::Green);


        }

        void moveObstacle(){
            setOposition(rand()%1150,rand()%500+150); // y : entre 150 et 650
            obstacles.setPosition(Oposition);    }

        //getters setters
        Vector2f getOposition(){
            return Oposition;  }
        RectangleShape getObstacle(){
            return obstacles;         } // need it to draw the Obstacle
        void setOposition(int x,int y){
            Oposition.x=x;
            Oposition.y=y;
        }

};
class Serpent{
    private :
        vector<RectangleShape> body;

        int dir; //0:right 1:left 2:up 3:down
        Fruit fruit;
        int speed=50;
        Vector2f sposition;
        RenderWindow window;
        Event event;
        RectangleShape rect;
        int m_score;
        vector<int> Highscores;
        Obstacle obstacle;
        int aide;
        bool k;

    public :
        Serpent(){
            window.create(VideoMode(1200, 700), "My Program");
            window.setFramerateLimit(10);



         }



        void grow(){

            rect.setSize(Vector2f(50, 50));
            rect.setFillColor(sf::Color::Yellow);

                if (body.empty()){
                    rect.setPosition(320, 256);
                }
                else{
                    rect.setPosition(body[body.size() - 1].getPosition().x - rect.getSize().x, body[body.size() - 1].getPosition().y);

                }

                body.push_back(rect);
        }
        void input(){
            Event event;

            while (window.pollEvent(event)) {
                // Window closed
                if (event.type == Event::Closed) {
                    window.close();
                }



                // Quitter
                    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                        body.clear();
                        Highscores.clear();
                        window.close();
                }

            }
            if(event.key.code == Keyboard::Right && dir!=1 && aide!=0)    dir=0;   // 0:right 1:left 2:up 3:down
            else if(event.key.code == Keyboard::Left && dir!=0 &&aide!=0)    dir=1;
            else if(event.key.code == Keyboard::Up && dir!=3 && aide!=0)      dir=2;
            else if(event.key.code == Keyboard::Down && dir!=2 && aide!=0)    dir=3;
            if( event.key.code == Keyboard::R && aide==0) reset(); // rejouer si on perd en appuyant sr R
        }
       /* void input(){
            Event event{};

            while (window.pollEvent(event)) {
                // Window closed
                if (event.type == Event::Closed) {
                    window.close();
                }

                // Handle Keyboard Input
                if (event.type == Event::KeyPressed) {
                // Quit
                    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                        body.clear();
                        Highscores.clear();
                        window.close();
                }
                }
            }
            if(event.key.code == sf::Keyboard::Right && dir!=1 && aide!=0)        dir=0;
            else if(event.key.code == sf::Keyboard::Left && dir!=0 && aide!=0)    dir=1;
            else if(event.key.code == sf::Keyboard::Up && dir!=3 && aide!=0)      dir=2;
            else if(event.key.code == sf::Keyboard::Down && dir!=2 && aide!=0)    dir=3;
            if( event.key.code == Keyboard::R && aide==0 ) reset();

        }*/


        void movebody(){
          if(aide==1){  if (body.size() > 1)
                for (unsigned int i = body.size() - 1; i > 0; i--)
                    body[i].setPosition(Vector2f(body[i-1].getPosition().x, body[i-1].getPosition().y));



             if(dir==1)
                body[0].move(-speed, 0);


            else  if(dir==0)
                body[0].move(speed, 0);


            else  if(dir==2)

                body[0].move(0, -speed);


            else  if(dir==3)


                body[0].move(0, speed);

            if (body[0].getPosition().x < 0 )       body[0].setPosition(1150,body[0].getPosition().y);
            if (body[0].getPosition().x > 1150)     body[0].setPosition(0,body[0].getPosition().y);
            if (body[0].getPosition().y < 150 )       body[0].setPosition(body[0].getPosition().x,700);
            if (body[0].getPosition().y > 700 )     body[0].setPosition(body[0].getPosition().x,150);

          }

        }


        bool changefruitposition (){ //checks if we need to change fruit position

             if(body[0].getGlobalBounds().intersects(fruit.getFruit().getGlobalBounds()) ){

                 return true;
            }
                return false;
        }
        bool is_died(){
            if(body[0].getGlobalBounds().intersects(obstacle.getObstacle().getGlobalBounds()) ){
                return true;
            }
                return false;
        }

        bool is_injured_itself(){

            for (unsigned int i = 2; i < body.size(); i++){
                if(body[0].getGlobalBounds().intersects(body[i].getGlobalBounds()))
                    return true;
            }

            return false;


        }

        void draw() {
            Font font;
            RectangleShape rectangle;
            rectangle.setFillColor(Color::Black);
            rectangle.setSize(Vector2f(1200,150));
            Text scores;
            Text text;
            Text num;
            font.loadFromFile("Fonts/ARIBL0.ttf");
           //cadre du score


            window.clear(Color::Blue);
            window.draw(fruit.getFruit()); //draw apple
            window.draw(rectangle); //draw frame
            window.draw(obstacle.getObstacle()); //draw obstacles

            text.setFont(font);
            text.setCharacterSize(24);
            //text.setColor(Color::Red);
            text.setString("score = "+to_string(m_score));
            text.setPosition(200,0);
            text.setString("score = "+std::to_string(m_score));
            window.draw(text);
            int espace=0;

            scores.setFillColor(Color::White);
            scores.setFont(font);
            scores.setCharacterSize(24);


            text.setString("Highscores : ");
            text.setPosition(500,0);
            //text.setColor(Color:: Red);
            window.draw(text);
            //text.setString("BE CAREFULL GREEN FOOD ARE POISON !!!");
            //text.setPosition(100,50);
            //text.setColor(Color:: Red);
            //window.draw(text);
            if(aide==0){
            text.setString("(GAME OVER! Push R to restart ! )");
            text.setPosition(100,100);

            window.draw(text);
            }

                   for( int i=0;i<Highscores.size();i++){
                        scores.setString(to_string(Highscores[i]));

                        scores.setPosition(800,espace);
                        espace+=30;
                        window.draw(scores);

                   }
                    for (unsigned int i = 0; i < body.size(); i++)
                        window.draw(body[i]);

            window.display();
        }
        void reset(){

            body.clear();
            m_score=0;
            fruit.moveFruit();
            grow();
            aide=1;

            k=false;



        }


         void run(){
                dir=0;

                 k=false;

                aide=1;
                m_score=0;

                 int help;

                 fruit.moveFruit();

                 obstacle.moveObstacle();

             while (window.isOpen()) {
                input();
                movebody();

                 if(is_injured_itself()|| is_died())
                    aide=0;

                 if(changefruitposition()){
                    fruit.moveFruit();
                    grow();
                    obstacle.moveObstacle();
                     m_score+=10;

                }

                if (aide==0 && !k){
                        if(Highscores.size()<5) {
                            Highscores.push_back(m_score);

                            for(int i=0;i<Highscores.size()-1;i++)
                            for(int j=i+1;j<Highscores.size();j++)
                                if ( Highscores[i] < Highscores[j] ) {
                                    help = Highscores[i];
                                    Highscores[i] = Highscores[j];
                                    Highscores[j] = help;


                    }
                    }
                    else{

                            //comparison
                           if(m_score>Highscores[4])
                            for(int i=0;i<5;i++){
                                if(m_score>Highscores[i]){
                                    for(int j=4;j>i;j--){
                                        Highscores[j]=Highscores[j-1];
                                    }

                                    Highscores[i]=m_score;
                                    i+=10;
                                }

                            }


                }
                 k=true;

                 }





                draw();


        }
         }

        //getters nd setters
        vector<RectangleShape> getbody(){
            return body;
        }
        Fruit getfruit(){
            return fruit;
        }

        Vector2f getsposition(){
            return sposition;
        }
        void setsposition(Vector2f newposition){
             sposition=newposition;
        }

};
int main()
{


        Serpent snake;

        snake.grow();

    snake.run();

    return 0;
}
