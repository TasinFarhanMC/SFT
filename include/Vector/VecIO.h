#ifndef VECIO_H
#define VECIO_H

#ifdef __cplusplus
 extern "C" {
#endif

#include <Vector/Vector.h>
#include <stdio.h>

/**
 * @brief Writes a Buffer to a File
 * @param buff The Buffer
 * @param elem_size The Size of Each Element
 * @param size The Buffer Size
 * @param file The File Descriptor
 * @returns Success
*/
bool VecIO_Write_Buff(const void *buff, size_t elem_size, size_t size, FILE *file);

/**
 * @brief Reads a Buffer from a file
 * @param buff The Buffer
 * @param buff_capacity The Capacity of The Buffer
 * @param elem_size The Size of Each Element
 * @param size The Array Length Pointer
 * @param file The File Descriptor
 * @returns Success
 */
bool VecIO_Read_Buff(void *buff, size_t buff_capacity, size_t elem_size, size_t *size, FILE *file);


/**
 * @brief Writes a Vector to a file
 * @param vec The Vector
 * @param info The Vec_Info Pointer
 * @param file The File Descriptor
 * @returns Success
 */
bool VecIO_Write(const void *vec, const struct Vec_Info *info, FILE *file);

/**
 * @brief Reads a Vector from a file
 * @param vec The Pointer to the Vector
 * @param info The Pointer to the Vec_Info Pointer
 * @param elem_size The Size of Each Element
 * @param growth The Growth Factor
 * @param file The File Descriptor
 * @returns Success
 */
bool VecIO_Read(void **vec, struct Vec_Info **info, size_t elem_size, size_t growth, FILE *file);

/**
 * @brief Skips A Specific Numbers Vectors/Buffers From a file
 * @param count The Number of Vectors/Buffers
 * @param file The File Descriptor
 * @returns The Number of Vectors/Buffers Skiped
*/
size_t VecIO_Skip(size_t count, FILE *file);

#ifdef __cplusplus
 }
#endif

#endif
