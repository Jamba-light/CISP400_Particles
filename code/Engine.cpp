#include "Engine.h"

Engine::Engine()
{
    unsigned int width = VideoMode::getDesktopMode().width;
    unsigned int height = VideoMode::getDesktopMode().height;
    VideoMode vm(width, height);
    m_Window.create(vm, "Particles", Style::Default);
}

void Engine::run()
{
    Clock clock;

    //Given unit test
    cout << "Starting Particle unit tests..." << endl;
    Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
    p.unitTests();
    cout << "Unit tests complete.  Starting engine..." << endl;

    while (m_Window.isOpen())
    {
        Time dt = clock.restart();
        float dtAsSeconds = dt.asSeconds();
        input();
        update(dtAsSeconds);
        draw();       
    }
}

void Engine::input()
{
    Event event;
    while (m_Window.pollEvent(event))
    {
        if (event.type == Event::Closed)
        {
            // Quit the game when the window is closed
            m_Window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                std::cout << "the left button was pressed" << std::endl;
                std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                Vector2i mousePosition = Vector2i(event.mouseButton.x, event.mouseButton.y);

                //Loop to construct particles
                for (int i = 0; i < 5; i++)
                {
                    int numPoints = rand() % 50 + 25;
                    Particle p(m_Window, numPoints, mousePosition);
                }
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            m_Window.close();
        }
    }
}

void Engine::update(float dtAsSeconds)
{
    unsigned int count = 0;
    for (auto i = m_particles.begin(); i != m_particles.end();)
    {
        if (i->getTTL() > 0.0)
        {
            i->update(dtAsSeconds);
            ++i;
        }
        else
        {
            i = m_particles.erase(i);

        }
    }
}

void Engine::draw()
{ 
    m_Window.clear();
    for (size_t i = 0; i < m_particles.size(); ++i) 
    { 
        m_Window.draw(m_particles[i]); 
    } 
    m_Window.display();
}