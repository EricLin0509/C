# X-Macro

X-Macro 是一种宏技术，用于在编译时生成代码。它允许在编译时动态地生成代码，而不需要在运行时进行动态内存分配或函数调用

## 示例

假设现在我们有一个难度系统，通过使用不同的速度生成函数实现不同难度

```c
typedef int (*DifficultyFunc) (void);

int easy(void)
{
    return 1;
}

int medium(void)
{
    return 2;
}

int hard(void)
{
    return 3;
}

static const DifficultyFunc difficulty_funcs[] = {
    easy,
    medium,
    hard
};
```

但是如果我们现在需要添加一个非常难的难度，那么很有可能会忘记添加到 `difficulty_funcs` 数组中

为解决这个问题，我们可以使用X-Macro技术

## 使用 X-Macro

1. 首先我们需要定义一组数据，这些数据将用于生成代码

```c
#define DIFFICULTIES \
    DIFFICULTY(EASY, 1) \
    DIFFICULTY(MEDIUM, 2) \
    DIFFICULTY(HARD, 3) \
```

2. 然后我们需要定义X-Macro，它将用于生成函数代码

由于预处理器的限制，我们无法直接写成 `difficulty_name`，因此我们**需要在 `name` 前面加上 `##` 通配符**才行

```c
#define DIFFICULTY(name, value) \
    int difficulty_##name(void) \
    { \
        return value; \
    }
DIFFICULTIES
#undef DIFFICULTY
```

3. 最后我们需要定义一个数组，用于存储函数指针

```c
#define DIFFICULTY(name, value) difficulty_##name,
static const DifficultyFunc difficulty_funcs[] = {
    DIFFICULTIES
};
#undef DIFFICULTY
```

## 验证

我们可以使用 `cpp` (C Preprocessor) 命令来验证X-Macro是否正确生成代码

```c
typedef int (*DifficultyFunc) (void);

int difficulty_EASY(void) { return 1; } int difficulty_MEDIUM(void) { return 2; } int difficulty_HARD(void) { return 3; }



static const DifficultyFunc difficulty_funcs[] = {
    difficulty_EASY, difficulty_MEDIUM, difficulty_HARD,
};
```

## 新增难度

现在我们已经定义了X-Macro，我们只需要在 `DIFFICULTIES` 中添加新的难度即可

```c
#define DIFFICULTIES \
    DIFFICULTY(EASY, 1) \
    DIFFICULTY(MEDIUM, 2) \
    DIFFICULTY(HARD, 3) \
    DIFFICULTY(EXPERT, 4) \
```

然后重新编译代码，就可以看到新增的难度已经生成了

```c
typedef int (*DifficultyFunc) (void);

int difficulty_EASY(void) { return 1; } int difficulty_MEDIUM(void) { return 2; } int difficulty_HARD(void) { return 3; } int difficulty_EXPERT(void) { return 4; }



static const DifficultyFunc difficulty_funcs[] = {
    difficulty_EASY, difficulty_MEDIUM, difficulty_HARD, difficulty_EXPERT,
};
```