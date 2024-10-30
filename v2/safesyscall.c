/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safesyscall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:19:01 by mes-salh          #+#    #+#             */
/*   Updated: 2024/10/29 17:33:12 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosofers.h"

void    *safe_malloc(size_t size)
{
    void    *ptr;

    ptr = malloc(size);
    if (!ptr)
    {
        printf("Error: malloc failed\n");
        exit(1);
    }
    return (ptr);
}

void    safe_mutex_init(pthread_mutex_t *mutex)
{
    if (pthread_mutex_init(mutex, NULL))
    {
        printf("Error: mutex init failed\n");
        exit(1);
    }
}

void    safe_mutex_lock(pthread_mutex_t *mutex)
{
    if (pthread_mutex_lock(mutex))
    {
        printf("Error: mutex lock failed\n");
        exit(1);
    }
}

void    safe_mutex_unlock(pthread_mutex_t *mutex)
{
    if (pthread_mutex_unlock(mutex))
    {
        printf("Error: mutex unlock failed\n");
        exit(1);
    }
}

void    safe_mutex_destroy(pthread_mutex_t *mutex)
{
    if (pthread_mutex_destroy(mutex))
    {
        printf("Error: mutex destroy failed\n");
        exit(1);
    }
}

void    safe_thread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg)
{
    if (pthread_create(thread, attr, start_routine, arg))
    {
        printf("Error: thread create failed\n");
        exit(1);
    }
}

void    safe_thread_join(pthread_t thread, void **retval)
{
    if (pthread_join(thread, retval))
    {
        printf("Error: thread join failed\n");
        exit(1);
    }
}

void    safe_thread_detach(pthread_t thread)
{
    if (pthread_detach(thread))
    {
        printf("Error: thread detach failed\n");
        exit(1);
    }
}