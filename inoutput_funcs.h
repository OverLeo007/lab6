#ifndef UNTITLED_INOUTPUT_FUNCS_H
#define UNTITLED_INOUTPUT_FUNCS_H


/*!
 * \brief считывает строку неограниченной длины из консоли
 * \details считывает строку расширяя память для нее при нехватки таковой
 * \return считанная строка
 */
char *input_string();

/*!
 * \brief считывает целочисленное значение длины до 4 символов с консоли
 * \return считанное число
 */
int input_int();

/*!
 * \brief провереяет переданное значение на возможность преобразования его в int
 * \return 1 если не является числом 0 если является
 */
int input_int_check(char value_array[]);

#endif //UNTITLED_INOUTPUT_FUNCS_H
