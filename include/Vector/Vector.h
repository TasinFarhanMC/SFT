#pragma once
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>

// This holds the information about the vector
struct Vec_Info {
  size_t elem_size;
  size_t size;
  size_t capacity;
  size_t growth;
};

/**
 * @brief Creates A Vector
 * @param vec The Pointer to the Vector Pointer
 * @param info The Pointer to the Vec_Info Struct Pointer
 * @param elem_size The Size of each element in bytes
 * @param growth The Size of the chunk that will be allocated for growing the Vector
 * @return Success
 */
bool Vec_Create(void** vec, struct Vec_Info** info, size_t elem_size, size_t growth);

/**
 * @brief Deallocates A Vector
 * @param vec The Pointer to the Vector Pointer
 * @param info The Pointer to the Vec_Info Struct Pointer
 */
#define Vec_Free(vec, info) do {\
  free(vec);\
  free(info);\
} while (0)

/**
 * @brief Reserves Size for the Vector
 * @param vec The Pointer to the Vector Pointer
 * @param info The Vec_Info Pointer
 * @param capacity The new total capacity
 * @return Success
 */
bool Vec_Reserve(void** vec, struct Vec_Info* info, size_t capacity);

/**
 * @brief Resizes the Vector | Uninitialized bytes will be set to 0
 * @param vec The Pointer to the Vector Pointer
 * @param info The Vec_Info Pointer
 * @param size The new total size
 * @return Success
 */
bool Vec_Resize(void** vec, struct Vec_Info* info, size_t size);

/**
 * @brief Shrinks the Vector by removing unused capacity
 * @param vec The Pointer to the Vector Pointer
 * @param info The Vec_Info Pointer
 * @return Success
 */
bool Vec_Shrink_To_Fit(void** vec, struct Vec_Info* info);

/**
 * @brief Gives the index of the first element of the Vector | Returs -1 if vector Size is 0
 * @param info The Vec_Info Pointer
 */
#define Vec_Front(info) (0 - (info->size <= 0))

/**
 * @brief Gives the index of the last element of the Vector | Returs -1 if vector Size is 0
 * @param info The Vec_Info Pointer
 */
#define Vec_Back(info) (info->size - 1)

/**
 * @brief Pushes a amount of elements to the Vector
 * @param vec The Pointer to the Vector Pointer
 * @param info The Vec_Info Pointer
 * @param data The Pointer to the pushed data
 * @param size The Size of the pushed data
 * @return Success
 */
bool Vec_Push(void** vec, struct Vec_Info* info, const void* data, size_t size);

/**
 * @brief Pops a amount of elements to the Vector
 * @param info The Vec_Info Pointer
 * @param count The Number of elements to pop
 * @return Number of Elements poped
 */
size_t Vec_Pop(struct Vec_Info* info, size_t count);

/**
 * @brief Insert a amount of elements to the Vector in the current size
 * @param vec The Pointer to the Vector Pointer
 * @param info The Vec_Info Pointer
 * @param pos The Position Index to insert
 * @param data The Pointer to the pushed data
 * @param size The Size of the inserted data
 * @return Success
 */
bool Vec_Insert(void** vec, struct Vec_Info* info, size_t pos, const void* data, size_t size);

/**
 * @brief Erases a amount of elements to the Vector in the current size
 * @param vec The Pointer to the Vector Pointer
 * @param info The Vec_Info Pointer
 * @param pos The Position Index to insert
 * @param count The Number of Elemenrs to erase
 * @return Number of erased Elements
 */
size_t Vec_Erase(void** vec, struct Vec_Info* info, size_t pos, size_t count);

/**
 * @brief Returns The size of the Vector
 * @param info The Vec_Info Pointer
 */
#define Vec_Size(info) (info->size)

/**
 * @brief Returns The capacity of the Vector
 * @param info The Vec_Info Pointer
 */
#define Vec_Capacity(info) (info->capacity)

/**
 * @brief Checks if the Vector is empty
 * @param info The Vec_Info Pointer
 */
#define Vec_Empty(info) (info->size == 0)

/**
 * @brief Clears the Vector
 * @param info The Vec_Info Pointer
 */
#define Vec_Clear(info) (info->size = 0)
