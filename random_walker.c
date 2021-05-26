#include <stdio.h>
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <stdlib.h> //for srand and rand
#include <time.h>
#include <math.h>

int main()
{
    srand(time(0));
    int direction;
    float step_size = 1;
    float circle_radius = 1.0;

    /* Render resolution */
    int window_width = 720;
    int window_height = 720;

    sfVector2i mouse_pos;
    sfVector2f text_origin = {60, 0};
    sfVector2f txt_pos = {window_width / 2, 0};
    sfVector2f circle_pos = {window_width / 2, window_height / 2};
    sfVideoMode mode = {window_width, window_height, 32};
    sfContextSettings settings = {.antialiasingLevel = 1};
    sfRenderWindow *window;
    sfFont *font;
    sfText *text;
    sfCircleShape *circle;
    sfEvent event;

    /* Create the main window */
    window = sfRenderWindow_create(mode, "CSFML Random Walker", sfNone, &settings);
    if (!window)
        return EXIT_FAILURE;

    /* Create a graphical text to display */
    font = sfFont_createFromFile("Raleway-Medium.ttf");
    if (!font)
        return EXIT_FAILURE;
    text = sfText_create();
    sfText_setString(text, "Random Walker");
    sfText_setFont(text, font);
    sfText_setOrigin(text, text_origin);
    sfText_setPosition(text, txt_pos);
    sfText_setCharacterSize(text, 25);

    /* Make a circle */
    circle = sfCircleShape_create();
    sfCircleShape_setFillColor(circle, sfWhite);

    /* Start the game loop */
    while (sfRenderWindow_isOpen(window))
    {
        /* Process events */
        while (sfRenderWindow_pollEvent(window, &event))
        {
            /* Close Window : exit */
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
            else if (event.type == sfEvtKeyPressed)
            {
                if (event.key.code == sfKeyUp)
                    step_size += 0.1f;
                else if (event.key.code == sfKeyDown)
                    step_size -= 0.1f;
                else if (event.key.code == sfKeyAdd)
                    circle_radius += 0.1f;
                else if (event.key.code == sfKeySubtract)
                    circle_radius -= 0.1f;
            }
            sfCircleShape_setRadius(circle, circle_radius);
        }

        /* Choosing a random direction */
        direction = (rand() % 4);

        /* Updating the position of the circle */
        switch (direction)
        {
        case 0:
            circle_pos.x += step_size;
            break;
        case 1:
            circle_pos.y += step_size;
            break;
        case 2:
            circle_pos.x -= step_size;
            break;
        case 3:
            circle_pos.y -= step_size;
            break;
        }
        sfCircleShape_setPosition(circle, circle_pos);

        /* Check if the point is out of the window */
        if (circle_pos.x < 0 || circle_pos.x > window_width)
            circle_pos.x = window_width / 2;
        if (circle_pos.y < 0 || circle_pos.y > window_height)
            circle_pos.y = window_height / 2;

        /* Draw the text */
        sfRenderWindow_drawText(window, text, NULL);

        /* Draw the shapes */
        sfRenderWindow_drawCircleShape(window, circle, NULL);

        /* Update the window */
        sfRenderWindow_display(window);
    }

    /* Clear the screen */
    sfRenderWindow_clear(window, sfBlack);

    /* Cleanup Resources */
    sfText_destroy(text);
    sfFont_destroy(font);
    sfRenderWindow_destroy(window);
    sfCircleShape_destroy(circle);

    return EXIT_SUCCESS;
}