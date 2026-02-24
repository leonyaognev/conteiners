# Стиль комментариев в файлах реализации

## Общие принципы

- Используются **однострочные комментарии** в стиле `// ...`
- Комментарии преимущественно на **Английском языке**
- Описывают логику работы, а не интерфейс

## Типичные примеры комментариев

### Описание логики

```cpp
// If we reached the sentinel node of the other tree,
// return our own sentinel to maintain structural consistency.
if (n == otherNil) {
    return nil;
}

// Create a new node copying the value
Node* x = new Node(n->value);

// Recursively copy the right subtree
x->right = copyTree(n->right, otherNil);
```

### Пометки о исправлениях

```cpp
for (size_t i = 0; i < _size; i++) {  // <-- ИСПРАВЛЕНО
    new (temp + i) T(std::move(_data[i]));
    _data[i].~T();
}
```

### Пометки об удалении

```cpp
// bool go_left = false; // УДАЛЕН: Не нужен
```

### Описательные комментарии

```cpp
// destroy elements we did not copy
for (size_t i = minSize; i < _size; i++) {
    _data[i].~T();
}
```

### Заголовки секций

```cpp
/**-----------------------------
 *         ARRAY METHODS
 *------------------------------
 */
```

## Паттерны комментариев

| Паттерн                    | Пример                                   |
| -------------------------- | ---------------------------------------- |
| Описание что делает строка | `// Start from the root`                 |
| Пометка об исправлении     | `// <-- ИСПРАВЛЕНО`                      |
| Пометка об удалении        | `// УДАЛЕН: Не нужен`                    |
| Описание блока             | `// If we hit NIL, this branch is empty` |
| Разделитель                | `/**----...----*/`                       |

## Ключевые особенности

1. **Английский язык** - основной язык комментариев
2. **Простота** - короткие, понятные комментарии
3. **Алгоритмичность** - описывают логику и алгоритмы
4. **Английский** - иногда встречается для технических терминов

## Что НЕ нужно комментировать

- Очевидные вещи (инкремент счётчика)
- Тривиальные присваивания
- Стандартные операции

## Примеры из кода

```cpp
// Fix red-black properties after insertion
while (z != root && z->parent->color == Red) {

// Node constructor:
// newly created nodes are red by default, following RB-tree rules.
Node(const T& v) : value(v), ... , color(Red) {

// If sibling is red, rotate and recolor to convert case
if (w->color == Red) {
```

## Рекомендации

1. Комментируй сложную логику
2. Используй пометки при исправлениях багов
3. Пиши на русском для личных заметок
4. Не злоупотребляй комментариями - код должен быть самодокументируемым
