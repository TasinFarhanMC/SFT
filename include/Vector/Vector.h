#pragma once
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

// Holds the information about the vector
struct Vec_Info {
  size_t elem_size; // Hold the Size of a element is bytes
  size_t size; // Holds the Size of the Vector
  size_t capacity; // Holds the Capacity of The Vector
  size_t growth; // Holds The Growth Factor
};

/**
 * @brief Initializes A Vector
 * @param data The Pointer to the Vector
 * @param info The Pointer to the Vec_Info
 * @param elem_size The Size of each element in bytes
 * @param growth The Growth Factor
 * @return Success
 */
bool Vec_Init(void** data, struct Vec_Info* info, size_t elem_size, size_t growth);

#define Vec_Free(data) free(data)

/**
 * @brief Reserves Size for the Vector
 * @param data The Pointer to the Vector
 * @param info The Pointer to the Vec_Info
 * @param capacity The new total Capacity
 * @return Success
 */
bool Vec_Reserve(void** data, struct Vec_Info* info, size_t capacity);

/**
 * @brief Resizes the Vector | Uninitialized bytes will be set to 0
 * @param data The Pointer to the Vector
 * @param info The Pointer to the Vec_Info
 * @param size The new total size
 * @return Success
 */
bool Vec_Resize(void** data, struct Vec_Info* info, size_t size);

/**
 * @brief Shrinks the Vector by removing unused capacity
 * @param data The Pointer to the Vector
 * @param info The Pointer to the Vec_Info
 * @return Success
 */
bool Vec_Shrink_To_Fit(void** data, struct Vec_Info* info);

/**
 * @brief Pushes a amount of elements to the Vector
 * @param data The Pointer to the Vector
 * @param info The Pointer to the Vec_Info
 * @param push_data The Pushed Data
 * @param push_size The Size of the Pushed Data
 * @return Success
 */
bool Vec_Push(void** data, struct Vec_Info* info, const void* push_data, size_t push_size);

/**
 * @brief Pops a amount of elements to the Vector
 * @param info The Pointer to the Vec_Info
 * @param count The Number of elements to pop
 * @return Number of Elements poped
 */
size_t Vec_Pop(struct Vec_Info* info, size_t count);

/**
 * @brief Insert a amount of elements to the Vector in the current size
 * @param data The Pointer to the Vector
 * @param info The Pointer to the Vec_Info
 * @param pos The Position Index to insert
 * @param insert_data The Inserted Data
 * @param insert_size The Size of the Inserted Data
 * @return Success
 */
bool Vec_Insert(void** data, struct Vec_Info* info, size_t pos, const void* insert_data, size_t insert_size);

/**
 * @brief Erases a amount of elements to the Vector in the current size
 * @param data The Pointer to the Vector
 * @param info The Pointer to the Vec_Info
 * @param pos The Position Index to insert
 * @param count The Number of Elements to erase
 * @return Number of Erased Elements
 */
size_t Vec_Erase(void** data, struct Vec_Info* info, size_t pos, size_t count);

/**
 * @brief Gives the index of the first element of the Vector | Returs -1 if vector Size is 0
 * @param info The Vec_Info
 */
#define Vec_Front(info) (0 - (info.size <= 0))

/**
 * @brief Gives the index of the last element of the Vector | Returs -1 if vector Size is 0
 * @param info The Vec_Info
 */
#define Vec_Back(info) (info.size - 1)

/**
 * @brief Returns The size of the Vector
 * @param info The Vec_Info
 */
#define Vec_Size(info) (info.size)

/**
 * @brief Returns The capacity of the Vector
 * @param info The Vec_Info
 */
#define Vec_Capacity(info) (info.capacity)

/**
 * @brief Checks if the Vector is empty
 * @param info The Vec_Info
 */
#define Vec_Empty(info) (info.size == 0)

/**
 * @brief Clears the Vector
 * @param info The Vec_Info
 */
#define Vec_Clear(info) (info.size = 0)

// Pre Defined Vectors

struct Int_Vec {
 int* data;
 struct Vec_Info info;
};

struct Int8_Vec {
 int8_t* data;
 struct Vec_Info info;
};

struct Int16_Vec {
 int16_t* data;
 struct Vec_Info info;
};

struct Int32_Vec {
 int32_t* data;
 struct Vec_Info info;
};

struct UInt8_Vec {
 uint8_t* data;
 struct Vec_Info info;
};

struct UInt16_Vec {
 uint16_t* data;
 struct Vec_Info info;
};

struct UInt32_Vec {
 uint32_t* data;
 struct Vec_Info info;
};

#ifdef __INT64_TYPE__
struct Int64_Vec {
 int64_t* data;
 struct Vec_Info info;
};

struct UInt64_Vec {
 uint64_t* data;
 struct Vec_Info info;
};
#endif