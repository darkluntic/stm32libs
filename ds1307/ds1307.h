/**
 * @file ds1307.h
 * Библиотека для работы с часами реального времени DS1307.
 */

#ifndef DS1307_H
#define	DS1307_H

#include <stdbool.h>
#include <stdint.h>
#include "errors/errors.h"
#include "future/future.h"
#include "i2c/i2c.h"
#include "ds1307mem.h"


#define E_DS1307_BUSY (E_BUSY)

//Адрес ds1307.
#define DS1307_I2C_ADDRESS 0x68

//Идентификатор передачи i2c для ds1307
#define DS1307_I2C_TRANSFER_ID DS1307_I2C_ADDRESS

//Тип статуса.
typedef enum _Ds1307_Status {
    DS1307_STATUS_NONE = 0, //!< Ничего не происходит.
    DS1307_STATUS_ERROR, //!< Ошибка.
    DS1307_STATUS_READ, //!< Начало чтения.
    DS1307_STATUS_READING, //!< Чтение.
    DS1307_STATUS_READED, //!< Прочитано.
    DS1307_STATUS_WRITE, //!< Начало записи.
    DS1307_STATUS_WRITING, //!< Запись.
    DS1307_STATUS_WRITED //!< Записано.
} ds1307_status_t;

//! Число сообщений i2c.
#define DS1307_I2C_MESSAGES_COUNT 2
//! Номер сообщения с адресом памяти.
#define DS1307_I2C_MESSAGE_ROM_ADDRESS 0
//! Номер сообщения с данными.
#define DS1307_I2C_MESSAGE_DATA 1

//! Сруктура DS1307.
typedef struct _Ds1307 {
    ds1307mem_t memory; //!< Образ памяти часов.
    i2c_bus_t* i2c; //!< Шина i2c.
    future_t future; //!< Будущее.
    ds1307_status_t status; //!< Статус обмена данными часов.
    uint8_t rom_address; //!< Адрес в памяти часов.
    i2c_message_t i2c_messages[DS1307_I2C_MESSAGES_COUNT];
} ds1307_t;


//! Структура даты и времени.
typedef struct Ds1307_DT {
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
    uint8_t day;
    uint8_t date;
    uint8_t month;
    uint8_t year;
    bool is_ampm;
    bool pm;
} ds1307_datetime_t;

/**
 * Инициализация RTC.
 * @return Код ошибки.
 */
extern err_t ds1307_init(ds1307_t* rtc, i2c_bus_t* i2c);

/**
 * Каллбэк i2c.
 * @param event Событие i2c.
 * @return true, если событие обработано, иначе false.
 */
extern bool ds1307_i2c_callback(ds1307_t* rtc);

/**
 * Получает флаг процесса выполнения операции.
 * @return Флаг процесса выполнения операции.
 */
extern bool ds1307_in_process(ds1307_t* rtc);

/**
 * Получает флаг завершения текущей операции.
 * @return Флаг завершения текущей операции.
 */
extern bool ds1307_done(ds1307_t* rtc);

/**
 * Получает статус.
 * @return Статус.
 */
extern ds1307_status_t ds1307_status(ds1307_t* rtc);

/**
 * Получает код ошибки.
 * @return Код ошибки.
 */
extern err_t ds1307_error(ds1307_t* rtc);

/**
 * Читает память.
 * @return Код ошибки.
 */
extern err_t ds1307_read(ds1307_t* rtc);

/**
 * Записывает память.
 * @return Код ошибки.
 */
extern err_t ds1307_write(ds1307_t* rtc);

/**
 * Получает дату и время.
 * @param datetime Дата и время.
 */
extern void ds1307_datetime_get(ds1307_t* rtc, ds1307_datetime_t* datetime);

/**
 * Устанавливает дату и время.
 * @param datetime Дата и время.
 */
extern void ds1307_datetime_set(ds1307_t* rtc, ds1307_datetime_t* datetime);

/**
 * Получает флаг запущенности часов.
 * @return Флаг запущенности часов.
 */
extern bool ds1307_running(ds1307_t* rtc);

/**
 * Устанавливает флаг запущенности часов.
 * @param running Флаг запущенности часов.
 */
extern void ds1307_set_running(ds1307_t* rtc, bool running);

/**
 * Записывает состояние часов.
 * @return Код ошибки.
 */
extern err_t ds1307_write_running(ds1307_t* rtc);

#endif	/* DS1307_H */

