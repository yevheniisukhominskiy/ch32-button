<p align="center">
    <img src="https://img.shields.io/badge/version-1.1-blue?style=for-the-badge" alt="Version">
    <img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/yevheniisukhominskiy/ch32-button?style=for-the-badge">
     <img src="https://img.shields.io/github/license/yevheniisukhominskiy/ch32-button?style=for-the-badge" alt="License">
</p>

# ch32-button

Мінімалістична С-бібліотека для роботи з кнопками на мікроконтролерах CH32V006. Швидка, легка та зрозуміла.

### Сумісність
- Платформа: **CH32V006**
- Залежності: [ch32-time](https://github.com/yevheniisukhominskiy/ch32-time) (бібліотека системного часу)

> [!IMPORTANT]
> Для роботи бібліотеки **обов'язково** потрібно ініціалізувати системний тік функцією `systick_init()` на початку програми.

### Зміст
- [Використання](#usage)
- [Приклад (базовий)](#example)
- [Приклад (з авто-інкрементом)](#example-adv)
- [Версії](#versions)
- [Встановлення](#install)

<a id="usage"></a>

## Використання

### Налаштування
Часові параметри (мс) за замовчуванням у `button.h`:
- `BTN_DEBOUNCE`: 30 мс
- `BTN_HOLD`: 1000 мс
- `BTN_STEP_HOLDING`: 1000 мс

### Основні функції
- `button_init(btn)` — ініціалізація структури кнопки. Пін автоматично налаштовується відповідно до обраного режиму (`mode`).
- `button_tick(btn)` — тікер, який обробляє стан кнопки. Має бути в головному циклі.
- `button_click(btn)` — повертає `true`, якщо був одиночний клік.
- `button_hold(btn)` — повертає `true`, якщо кнопку утримували довше `BTN_HOLD`.
- `button_holding(btn, period)` — повертає `true` через рівні проміжки часу, поки кнопка тримається затиснутою.

### Режими підтяжки (Mode_t)
- `PULL_UP` — внутрішня підтяжка до живлення (активний рівень LOW).
- `PULL_DOWN` — внутрішня підтяжка до землі (активний рівень HIGH).

<a id="example"></a>

## Приклад

Адаптований приклад на основі `example.c`:

```c
#include "debug.h"
#include "time.h"
#include "button.h"

// Створюємо структуру кнопки з налаштуваннями
Button_t btn1 = {
    .port = GPIOD,
    .pin = GPIO_Pin_7,
    .mode = PULL_UP,
};

int main(void) {
    SystemCoreClockUpdate();
    
    // Ініціалізація периферії
    RCC_PB2PeriphClockCmd(RCC_PB2Periph_GPIOD, ENABLE);

    // Ініціалізація системного таймеру (ОБОВ`ЯЗКОВА ЗАЛЕЖНІСТЬ)
    systick_init();

    // Ініціалізація кнопки
    button_init(&btn1);

    while(1) {
        // Опитування стану кнопки
        button_tick(&btn1);

        // Перевірка одиночного кліку
        if (button_click(&btn1)) {
            // Клік!
        } 
        
        // Перевірка утримання кнопки
        if (button_hold(&btn1)) {
            // Утримання!
        } 
        
        // Спрацювання кожні 200мс, поки кнопка затиснута
        if (button_holding(&btn1, 200)) {
            // Режим автоповтору...
        }
    }
}
```

<a id="versions"></a>

## Версії
- **v1.0** — реліз базового функціоналу.
- **v1.1** — перероблена ініціалізація, додано вибір підтяжки (PULL_UP/PULL_DOWN).

<a id="install"></a>

## Встановлення
Просто скопіюйте папку `lib` у ваш проєкт та підключіть заголовок `#include "button.h"`.
Забезпечте наявність бібліотеки [ch32-time](https://github.com/yevheniisukhominskiy/ch32-time) у вашому проєкті.

## Баги та зворотний зв'язок
Створюйте **Issue** у цьому репозиторії або надсилайте Pull Request-и.
