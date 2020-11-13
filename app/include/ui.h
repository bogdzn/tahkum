/**
 * \file ui.h
 * \brief implementation of GLFW library
 * \author Bogdan G.
 * \date 11/11/2020
 */

#ifndef TAHKUM_UI
#define TAHKUM_UI

#include "parser.h"
#include "exec.h"
#include <GLFW/glfw3.h>

/**
  * \typedef struct context_s ctx_t
  * \brief holds relevant information regarding program context
  * \param user_settings user_defined settings, see parser.h
  * \param window GLFW window !
  */
typedef struct context_s
{
    settings_t user_settings;
    GLFWwindow *window;
    socket_t video;
    socket_t ryzectl;
} ctx_t;

// ressources.c
/**
  * \fn int init_ctx(ctx_t *user_context, int ac, char **av)
  * \brief sets up ui context, and user settings
  *
  * \param address of a `ctx_t` struct.
  * \param ac number of arguments
  * \param av array of arguments
  * \return 0 if successfull, 1 if not.
  */
int init_ctx(ctx_t *user_context, int ac, char **av);

/**
  * \fn void destroy_ctx(ctx_t user_context)
  * \brief destroys user context
  *
  * \param instance of a `ctx_t` struct.
  */
void destroy_ctx(ctx_t user_context);

// events.c

// loops.c
#endif /* TAHKUM_UI */
