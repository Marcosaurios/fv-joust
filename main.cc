#include <iostream>
#include <SFML/Graphics.hpp>

#define kVel 5


using namespace sf;
using namespace std;

void loop(RenderWindow &window);

int main() {
    //Creamos una ventana (640x480) 550 394
    RenderWindow window(sf::VideoMode(550, 394), "P0. Fundamentos de los Videojuegos. DCCIA");

    //Bucle del juego
    loop(window);

    //git
    return 0;
}


void loop(RenderWindow &window)
{
    // Velocity vector
    float sx,sy=0;
    Vector2f speed(sx,sy);
    
    //Cargo la imagen donde reside la textura del sprite
    Texture tex_ini;
    if (!tex_ini.loadFromFile("resources/spritesheet.png")) {
        cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }
    //Y creo el spritesheet a partir de la imagen anterior
    Sprite sprite(tex_ini);
    //Le pongo el centroide donde corresponde
    sprite.setOrigin(0, 0);
    //Cojo el sprite que me interesa por defecto del sheet
    sprite.setTextureRect(sf::IntRect(8, 35, 16, 20));
    // Lo dispongo en el centro de la pantalla
    sprite.setPosition(320, 240);
    // Background setting:
    Texture bg;
    if (!bg.loadFromFile("resources/joust_bg.png")) {
        cerr << "Background not loaded!";
    }
    Sprite background(bg);

    // Rectangles bounding boxes for collisions
    RectangleShape rect1({60,10});
    rect1.setPosition({0,120});
    rect1.setFillColor(Color(255,255,255,128));
    
    RectangleShape rect2({160,17});
    rect2.setPosition({180,140});
    rect2.setFillColor(Color(255,255,255,128));
    
    RectangleShape rect3({75,10});
    rect3.setPosition({475,120});
    rect3.setFillColor(Color(255,255,255,128));
    
    RectangleShape rect4({110,15});
    rect4.setPosition({0,235});
    rect4.setFillColor(Color(255,255,255,128));
    
    RectangleShape rect5({110,15});
    rect5.setPosition({205,265});
    rect5.setFillColor(Color(255,255,255,128));
    
    RectangleShape rect6({110,15});
    rect6.setPosition({380,220});
    rect6.setFillColor(Color(255,255,255,128));
    
    RectangleShape rect7({75,10});
    rect7.setPosition({475,235});
    rect7.setFillColor(Color(255,255,255,128));
    
    RectangleShape base({550,50});
    base.setPosition({0,344});
    base.setFillColor(Color(255,255,255,128));
    
    
    
    while (window.isOpen()) {
        //Bucle de obtención de eventos
        sf::Event event;
        while (window.pollEvent(event)) {

            switch (event.type) {

                    //Si se recibe el evento de cerrar la ventana la cierro
                case sf::Event::Closed:
                    window.close();
                    break;

                    //Se pulsó una tecla, imprimo su codigo
                case sf::Event::KeyPressed:

                    //Verifico si se pulsa alguna tecla de movimiento
                    switch (event.key.code) {

                            //Mapeo del cursor
                        case sf::Keyboard::Right:
                            sprite.setTextureRect(sf::IntRect(69, 35, 16, 20));
                            //Escala por defecto
                            sprite.setScale(1, 1);
                            sprite.move(kVel, 0);
                            break;
                        case sf::Keyboard::Left:
                            sprite.setTextureRect(sf::IntRect(69, 35, 16, 20));
                            //Reflejo vertical
                            sprite.setScale(-1, 1);
                            sprite.move(-kVel, 0);break;
                        case Keyboard::LControl:
                            sprite.setTextureRect(IntRect(30, 14, 16, 13));
                            sprite.move(0, -kVel);
                            break;
                            /*
                            case sf::Keyboard::Up:
                                sprite.setTextureRect(sf::IntRect(0*75, 3*75, 75, 75));
                                sprite.move(0,-kVel); 
                            break;
                        
                            case sf::Keyboard::Down:
                                sprite.setTextureRect(sf::IntRect(0*75, 0*75, 75, 75));
                                sprite.move(0,kVel); 
                            break;
                             * */


                            //Tecla ESC para salir
                        case sf::Keyboard::Escape:
                            window.close();
                            break;

                            //Cualquier tecla desconocida se imprime por pantalla su código
                        default:
                            std::cout << event.key.code << std::endl;
                            break;

                    }

            }

        }
        
        window.clear();
        window.draw(background);
        window.draw(sprite);
        window.draw(rect1);
        window.draw(rect2);
        window.draw(rect3);
        window.draw(rect4);
        window.draw(rect5);
        window.draw(rect6);
        window.draw(rect7);
        window.draw(base);
        
        
        
        
        window.display();
    }
}