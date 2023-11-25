/*
MIT License

Copyright (c) 2020-2023 Hirrolot

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
// The official repository: <https://github.com/Hirrolot/datatype99>.
/**
 * @file
 * Static assertions.
 *
 * For the sake of convenience, this header automatically includes `metalang99/bool.h`.
 *
 * @note [C99] Any of the following assertion macros must **not** appear on the same line number
 * twice with itself as well as with any other Metalang99 assertion macro.
 * @note [C11] The following assertion macros expand to `_Static_assert` and, therefore, can be used
 * on the same line twice.
 */
// GCC 4.6 Release Series: <https://gcc.gnu.org/gcc-4.6/changes.html>.
// ML99_PRIV_C11_STATIC_ASSERT_AVAILABLE {
/*
 * On MSVC, `__STDC__` expands to 0 if the `\Za` option was not specified, but the thing is that it
 * nevertheless supports C11's `_Static_assert`.
 *
 * MSVC Standard predefined macros:
 * <https://docs.microsoft.com/en-us/cpp/preprocessor/predefined-macros#standard-predefined-macros>.
 */
// } (ML99_PRIV_C11_STATIC_ASSERT_AVAILABLE)
// ML99_PRIV_EMIT_ERROR {
// } (ML99_PRIV_EMIT_ERROR)

/**
 * @file
 * Boolean algebra.
 */
/*
 * contains_comma(1, 2, 3) ->
 * x_as_comma(1, 2, 3, ,, ~) ->
 * contains_comma_result(2, 0, 1, ~) ->
 * 1
 *
 * contains_comma(AB#C) ->
 * x_as_comma(AB#C, ,, ~) ->
 * contains_comma_result(,,0, 1, ~) ->
 * 0
 * */
/**
 * Checks whether @p x takes the form `(...) (...) ...`.
 *
 * This often happens when you miss a comma between items:
 *  - `v(123) v(456)`
 *  - `(Foo, int) (Bar, int)` (as in Datatype99)
 *  - etc.
 */

/**
 * @file
 * The core metalanguage.
 */
// Explanation is in the spec: <https://github.com/Hirrolot/metalang99/blob/master/spec/spec.pdf>.
/*
 * This recursion engine takes its roots from map-macro [1] and Cloak [2], with a few improvements:
 *
 *  - It can do many more expansions (roughly 1024 * 16 or 2^14).
 *
 *  - The expansion chain is linear: `ML99_PRIV_REC_0` invokes `ML99_PRIV_REC_1`, `ML99_PRIV_REC_1`
 * invokes `ML99_PRIV_REC_2`, and so on.
 *
 *  - If a given metaprogram does not require more expansions, then it will stop expanding. I.e.,
 * perform only as many expansions as needed. This is controlled by `ML99_PRIV_REC_NEXT`: if
 * `choice` is `0stop`, then just terminate the expansion chain.
 *
 *  - The last expander `ML99_PRIV_REC_1023` really results in a deferred `ML99_PRIV_REC_0`, not to
 * make it painted blue. Then, in `ML99_PRIV_REC_UNROLL_AUX`, this `ML99_PRIV_REC_0` is expanded
 * once again 16 times.
 *
 *  - It requires recursive macros to be written in CPS, continuation-passing style [3]. This is
 * controlled by `ML99_PRIV_REC_CONTINUE`: the `k` parameter stands for "continuation". `k` must
 * eventually expand to yet another `ML99_PRIV_REC_CONTINUE`. Also, there is a special continuation
 * called `ML99_PRIV_REC_STOP` -- it terminates the engine.
 *
 * The minimal usage example is located at `tests/eval/rec.c`.
 *
 * [1]: https://github.com/swansontec/map-macro
 * [2]: https://github.com/pfultz2/Cloak/wiki/C-Preprocessor-tricks,-tips,-and-idioms#recursion
 * [3]: https://en.wikipedia.org/wiki/Continuation-passing_style
 */
// clang-format off
// clang-format on
// clang-format off
// clang-format on
// Recursion hooks {
// } (Recursion hooks)
// Reduction rules {
// } (Reduction rules)
// Continuations {
/*
 * In this subroutine, we employ the following optimisation:
 *
 *  - If `evaluated_op` expands to many terms, we first evaluate these terms and accumulate them
 * (`ML99_PRIV_EVAL_0callUneval_K_1`).
 *  - Otherwise, we just paste a single term with the rest of the tail
 * (`ML99_PRIV_EVAL_0callUneval_K_0`).
 */
// } (Continuations)

/*
 * A closure has the form `(arity, f, ...)`, where `arity` is how many times `ML99_appl` can
 * be called for this closure, and `...` denotes the closure's environment.
 *
 * `ML99_appl` is described by the following algorithm:
 *  - If `f` is an identifier (like `FOO`):
 *    - If `f##_ARITY` is 1, then just call this function with provided arguments.
 *    - Otherwise, return `(f##_ARITY - 1, f, provided args...)`.
 *  - Otherwise (`f` is a closure):
 *    - If `arity` is 1, then just call `f` with its environment and provided arguments.
 *    - Otherwise, return `(arity - 1, f, env..., provided args...)`.
 *
 * Thus, each time except the last, `ML99_appl` extends a closure's environment with new
 * arguments; the last time, it calls `f` with its environment.
 */

/**
 * Evaluates a metaprogram.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/lang.h>
 *
 * #define F_IMPL(x, y) v(x + y)
 *
 * ML99_EVAL(v(abc ~ 123), ML99_call(F, v(1, 2)))
 * @endcode
 */
/**
 * Invokes a metafunction with arguments.
 */
/**
 * Invokes a metafunction @p ident with unevaluated arguments.
 *
 * It is semantically the same as `ML99_call(ident, v(...))` but performs one less reduction
 * steps.
 */
/**
 * Applies arguments to @p f.
 *
 * This function implements [partial
 * application](https://en.wikipedia.org/wiki/Partial_application): instead of invoking a
 * metafunction with all arguments at once, you specify each argument separately. This concept
 * allows better re-use of metafunctions by specifying some arguments immediately, and the other
 * arguments later, even in different execution contexts (for example, see this [SO
 * answer](https://stackoverflow.com/a/12414292/13166656)).
 *
 * @p f must be either a term reducing to a macro name or a term obtained via another call to
 * #ML99_appl. If @p f is a macro name, then a macro named `<f>_ARITY` (its arity specifier)
 * must denote how many times @p f will be applied to its arguments. (In Metalang99, an arity is an
 * intentionally more flexible concept than just a number of parameters, see below.) Each time
 * #ML99_appl is invoked, it accumulates provided variadic arguments and decrements the arity
 * of @p f; when the arity of @p f is already 1, it eventually calls the initial @p f with all the
 * accumulated arguments and provided variadic arguments.
 *
 * Most often, an arity specifier denotes a count of all named parameters plus 1 if a macro is
 * variadic (all the functions in the standard library follow this pattern). However, feel free to
 * specify arities as you wish, with regard to the aforementioned semantics; for example, you can
 * have a macro accepting `x, y, z` with an arity specifier `2`, then you must invoke
 * #ML99_appl exactly 2 times (either `x` + `y, z` or `x, y` + `z`). One common pattern is to
 * match a head and a tail of variadic arguments:
 *
 * @code
 * #include <metalang99/lang.h>
 *
 * #define F_IMPL(x, y, z, head, ...) // ...
 * #define F_ARITY 4
 * @endcode
 *
 * In this case, `x`, `y`, and `z` can be specified separately but other arguments all at once.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/lang.h>
 *
 * #define F_IMPL(x, y) v(x##y)
 * #define F_ARITY      2
 *
 * // ab
 * ML99_appl(ML99_appl(v(F), v(a)), v(b))
 * @endcode
 *
 * @note Currently, the maximum arity is #ML99_NAT_MAX. However, some compilers might not support
 * more than 127 macro parameters.
 */
/**
 * Applies @p a and @p b to @p f.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/lang.h>
 *
 * #define F_IMPL(x, y) v(x##y)
 * #define F_ARITY      2
 *
 * // ab
 * ML99_appl2(v(F), v(a), v(b))
 * @endcode
 */
/**
 * Applies @p a, @p b, and @p c to @p f.
 */
/**
 * Applies @p a, @p b, @p c, and @p d to @p f.
 */
/**
 * Functional composition of @p f and @p g.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/lang.h>
 *
 * #define F_IMPL(x) v((x + 1))
 * #define G_IMPL(x) v((x * 8))
 *
 * #define F_ARITY 1
 * #define G_ARITY 1
 *
 * // ((3 * 8) + 1)
 * ML99_appl(ML99_compose(v(F), v(G)), v(3))
 * @endcode
 */
/**
 * A value that is pasted as-is; no evaluation occurs on provided arguments.
 */
// clang-format off
/**
 * Emits a fatal error.
 *
 * @p f must be a macro name that has caused the error and the rest of arguments comprise the error
 * message.
 *
 * #ML99_fatal interprets its variadic arguments without preprocessor expansion -- i.e., they are
 * pasted as-is. This is intended because otherwise identifiers located in an error message may
 * stand for other macros that will be unintentionally expanded.
 *
 * # Examples
 *
 * [`playground.c`]
 * @code
 * #include <metalang99/lang.h>
 *
 * ML99_EVAL(ML99_fatal(F, the description of your error))
 * @endcode
 *
 * [`/bin/sh`]
 * @code{.txt}
 * playground.c:3:1: error: static assertion failed: "F: the description of your error"
 *     3 | ML99_EVAL(ML99_fatal(F, the description of your error))
 *       | ^~~~~~~~~
 * @endcode
 */
// clang-format on
/**
 * Immediately aborts the interpretation with evaluated arguments.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/lang.h>
 *
 * #define F_IMPL(x) v(~)
 *
 * // 123
 * ML99_call(F, ML99_abort(v(123)))
 * @endcode
 */
/**
 * A convenience macro to emphasise that your metafunction expands to more than one term.
 *
 * This macro just expands to provided arguments.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/lang.h>
 *
 * #define F_IMPL(x) ML99_TERMS(v(1), v(x), v(2))
 * @endcode
 */
/**
 * Delays evaluation for provided terms.
 *
 * `ML99_QUOTE(...)` is functionally equivalent to `v(...)`.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/lang.h>
 *
 * #define F_IMPL(x) v(~x)
 *
 * #define PROG ML99_TERMS(v(1), v(2), ML99_call(F, v(7)))
 *
 * // The same as `PROG` pasted into a source file.
 * ML99_EVAL(ML99_QUOTE(PROG))
 * @endcode
 */
// Arity specifiers {
// } (Arity specifiers)

/**
 * Truth.
 */
/**
 * Falsehood.
 */
/**
 * Logical negation.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/bool.h>
 *
 * // 1
 * ML99_not(v(0))
 *
 * // 0
 * ML99_not(v(1))
 * @endcode
 */
/**
 * Logical conjunction.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/bool.h>
 *
 * // 0
 * ML99_and(v(0), v(0))
 *
 * // 0
 * ML99_and(v(0), v(1))
 *
 * // 0
 * ML99_and(v(1), v(0))
 *
 * // 1
 * ML99_and(v(1), v(1))
 * @endcode
 */
/**
 * Logical inclusive OR.
 *
 * # Examples
 * @code
 * #include <metalang99/bool.h>
 *
 * // 0
 * ML99_or(v(0), v(0))
 *
 * // 1
 * ML99_or(v(0), v(1))
 *
 * // 1
 * ML99_or(v(1), v(0))
 *
 * // 1
 * ML99_or(v(1), v(1))
 * @endcode
 */
/**
 * Logical exclusive OR.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/bool.h>
 *
 * // 0
 * ML99_xor(v(0), v(0))
 *
 * // 1
 * ML99_xor(v(0), v(1))
 *
 * // 1
 * ML99_xor(v(1), v(0))
 *
 * // 0
 * ML99_xor(v(1), v(1))
 * @endcode
 */
/**
 * Tests @p x and @p y for equality.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/bool.h>
 *
 * // 1
 * ML99_boolEq(v(0), v(0))
 *
 * // 0
 * ML99_boolEq(v(0), v(1))
 *
 * // 0
 * ML99_boolEq(v(1), v(0))
 *
 * // 1
 * ML99_boolEq(v(1), v(1))
 * @endcode
 */
/**
 * Matches @p x against the two cases: if it is 0 or 1.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/bool.h>
 *
 * #define MATCH_1_IMPL() v(Billie)
 * #define MATCH_0_IMPL() v(Jean)
 *
 * // Billie
 * ML99_boolMatch(v(1), v(MATCH_))
 *
 * // Jean
 * ML99_boolMatch(v(0), v(MATCH_))
 * @endcode
 *
 * @note This function calls @p f with #ML99_call, so no partial application occurs, and so
 * arity specifiers are not needed.
 */
/**
 * The same as #ML99_boolMatch but provides additional arguments to all branches.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/bool.h>
 *
 * #define MATCH_1_IMPL(x, y, z) v(Billie ~ x y z)
 * #define MATCH_0_IMPL(x, y, z) v(Jean ~ x y z)
 *
 * // Billie ~ 1 2 3
 * ML99_boolMatchWithArgs(v(1), v(MATCH_), v(1, 2, 3))
 *
 * // Jean ~ 1 2 3
 * ML99_boolMatchWithArgs(v(0), v(MATCH_), v(1, 2, 3))
 * @endcode
 */
/**
 * If @p cond is true, evaluates to @p x, otherwise @p y.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/bool.h>
 *
 * // 123
 * ML99_if(v(1), v(123), v(18))
 *
 * // 18
 * ML99_if(v(0), v(123), v(18))
 * @endcode
 */
/**
 * The plain version of #ML99_if.
 *
 * This macro can imitate lazy evaluation: `ML99_IF(<cond>, <term>, <another-term>)` will expand to
 * one of the two terms, which can be evaluated further; if `<cond>` is 0, then `<term>` will
 * **not** be evaluated, and the same with `<another-term>`.
 *
 * @note @p x and @p y can possibly expand to commas. It means that you can supply `ML99_TERMS(...)`
 * as a branch, for example.
 */
// Arity specifiers {
// } (Arity specifiers)
/**
 * The same as #ML99_ASSERT but results in a Metalang99 term.
 *
 * It can be used inside other Metalang99-compliant macros, unlike #ML99_ASSERT, which uses
 * #ML99_EVAL internally.
 */
/**
 * Like #ML99_assert but compares @p lhs with @p rhs for equality (`==`).
 */
/**
 * Asserts `ML99_EVAL(expr)` at compile-time.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/assert.h>
 *
 * ML99_ASSERT(v(123 == 123));
 * @endcode
 */
/**
 * Asserts `ML99_EVAL(lhs) == ML99_EVAL(rhs)` at compile-time.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/assert.h>
 *
 * ML99_ASSERT_EQ(v(123), v(123));
 * @endcode
 */
/**
 * Asserts the C constant expression @p expr;
 * [static_assert](https://en.cppreference.com/w/c/error/static_assert) in pure C99.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/assert.h>
 *
 * ML99_ASSERT_UNEVAL(123 == 123);
 * @endcode
 */
/**
 * Asserts that `ML99_EVAL(expr)` is emptiness.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/assert.h>
 *
 * // Passes:
 * ML99_ASSERT_EMPTY(v());
 *
 * // Fails:
 * ML99_ASSERT_EMPTY(v(123));
 * @endcode
 */
/**
 * Asserts that @p expr is emptiness.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/assert.h>
 *
 * // Passes:
 * ML99_ASSERT_EMPTY_UNEVAL();
 *
 * // Fails:
 * ML99_ASSERT_EMPTY_UNEVAL(123);
 * @endcode
 */
// Arity specifiers {
// } (Arity specifiers)

/**
 * @file
 * Choice types: `(tag, ...)`.
 *
 * A choice type, also known as [tagged union], is represented as `(tag, ...)`, where `tag` is the
 * type of a value and `...` is the value. Perhaps the most common example of a choice type is a
 * binary tree:
 *
 * [[examples/binary_tree.c](https://github.com/Hirrolot/metalang99/blob/master/examples/binary_tree.c)]
 * @include binary_tree.c
 *
 * [tagged union]: https://en.wikipedia.org/wiki/Tagged_union
 */
/**
 * Constructs an instance of a choice type.
 *
 * # Examples
 *
 * See
 * [examples/binary_tree.c](https://github.com/Hirrolot/metalang99/blob/master/examples/binary_tree.c).
 *
 * @note Specify `~` if you do not want to supply data; then, to match it, write a `_` parameter to
 * ignore.
 */
/**
 * Evaluates to the tag of @p choice.
 *
 * This macro is essentially the same as `ML99_tupleGet(0)`.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/choice.h>
 *
 * // foo
 * ML99_choiceTag(ML99_choice(v(foo), v(1, 2, 3)))
 * @endcode
 */
/**
 * Evaluates to the data of @p choice.
 *
 * This macro is essentially the same as #ML99_tupleTail.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/choice.h>
 *
 * // 1, 2, 3
 * ML99_choiceData(ML99_choice(v(foo), v(1, 2, 3)))
 * @endcode
 */
/**
 * Matches the instance @p choice of a choice type.
 *
 * This macro results in `ML99_call(ML99_cat(matcher, ML99_choiceTag(choice)), <choice data>)`.
 *
 * # Examples
 *
 * See
 * [examples/binary_tree.c](https://github.com/Hirrolot/metalang99/blob/master/examples/binary_tree.c).
 */
/**
 * The same as #ML99_match but supplies additional arguments to all branches.
 *
 * This macro results in `ML99_call(ML99_cat(matcher, ML99_choiceTag(choice)), <choice data>,
 * args...)`.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/choice.h>
 *
 * #define MATCH_A_IMPL(x, y, z) v(x ~ y ~ z)
 *
 * // 123 ~ 456 ~ 789
 * ML99_matchWithArgs(ML99_choice(v(A), v(123)), v(MATCH_), v(456, 789))
 * @endcode
 */
// Arity specifiers {
// } (Arity specifiers)
/**
 * @file
 * A choice type with two cases.
 */
/**
 * @file
 * Identifiers: `[a-zA-Z0-9_]+`.
 *
 * An identifier is a sequence of characters. A character is one of:
 *
 *  - digits (`0123456789`),
 *  - lowercase letters (`abcdefghijklmnopqrstuvwxyz`),
 *  - uppercase letters (`ABCDEFGHIJKLMNOPQRSTUVWXYZ`),
 *  - the underscore character (`_`).
 *
 * For example, here are identifiers: `_ak39A`, `192_iAjP_2`, `r9`. But these are **not**
 * identifiers: `~18nA`, `o78*`, `3i#^hdd`.
 */
/**
 * Tells whether @p ident belongs to a set of identifiers defined by @p prefix.
 *
 * If `ML99_cat(prefix, ident)` exists, it must be an object-like macro which expands to `()`. If
 * so, `ML99_detectIdent(prefix, ident)` will expand to truth, otherwise (`ML99_cat(prefix, ident)`
 * does **not** exist), `ML99_detectIdent(prefix, ident)` will expand to falsehood.
 *
 * # Predefined detectors
 *
 *  - `ML99_UNDERSCORE_DETECTOR` detects the underscore character (`_`).
 *
 * # Examples
 *
 * @code
 * #include <metalang99/ident.h>
 *
 * #define FOO_x ()
 * #define FOO_y ()
 *
 * // 1
 * ML99_detectIdent(v(FOO_), v(x))
 *
 * // 1
 * ML99_detectIdent(v(FOO_), v(y))
 *
 * // 0
 * ML99_detectIdent(v(FOO_), v(z))
 *
 * // 1
 * ML99_detectIdent(v(ML99_UNDERSCORE_DETECTOR), v(_))
 * @endcode
 */
/**
 * Compares two identifiers @p x and @p y for equality.
 *
 * This macro is a shortcut to `ML99_detectIdent(ML99_cat3(prefix, x, v(_)), y)`.
 *
 * # Predefined detectors
 *
 *  - `ML99_C_KEYWORD_DETECTOR` detects all the [C11
 * keywords](https://en.cppreference.com/w/c/keyword).
 *  - `ML99_LOWERCASE_DETECTOR` detects lowercase letters (`abcdefghijklmnopqrstuvwxyz`).
 *  - `ML99_UPPERCASE_DETECTOR` detects uppercase letters (`ABCDEFGHIJKLMNOPQRSTUVWXYZ`).
 *  - `ML99_DIGIT_DETECTOR` detects digits (`0123456789`).
 *
 * # Examples
 *
 * @code
 * #include <metalang99/ident.h>
 *
 * #define FOO_x_x ()
 * #define FOO_y_y ()
 *
 * // 1
 * ML99_identEq(v(FOO_), v(x), v(x))
 *
 * // 1
 * ML99_identEq(v(FOO_), v(y), v(y))
 *
 * // 0
 * ML99_identEq(v(FOO_), v(x), v(y))
 *
 * // 1
 * ML99_identEq(v(ML99_C_KEYWORD_DETECTOR), v(while), v(while))
 * ML99_identEq(v(ML99_LOWERCASE_DETECTOR), v(x), v(x))
 * ML99_identEq(v(ML99_UPPERCASE_DETECTOR), v(X), v(X))
 * ML99_identEq(v(ML99_DIGIT_DETECTOR), v(5), v(5))
 * @endcode
 */
/**
 * Compares two characters @p x and @p y for equality.
 *
 * @p x and @p y can be any identifiers, though this function evaluates to true only for characters.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/ident.h>
 *
 * // 1
 * ML99_charEq(v(t), v(t))
 *
 * // 0
 * ML99_charEq(v(9), v(A))
 *
 * // 0
 * ML99_charEq(v(9), v(abcd))
 * @endcode
 */
/**
 * Tells whether the identifier @p x is a lowercase letter.
 */
/**
 * Tells whether the identifier @p x is an uppercase letter.
 */
/**
 * Tells whether the identifier @p x is a digit.
 */
/**
 * Tells whether the identifier @p x is a character.
 */
/**
 * Converts the Metalang99 character @p x to a C character literal.
 *
 * # Examples
 *
 * @code
 * #include <metalang/ident.h>
 *
 * // 't'
 * ML99_charLit(v(t))
 *
 * // '9'
 * ML99_charLit(v(9))
 *
 * // '_'
 * ML99_charLit(v(_))
 * @endcode
 *
 * @note The inverse of this function is impossible, i.e., you cannot get `q` from `'q'`.
 */
/**
 * Expands to all comma-separated lowercase letters.
 *
 * This macro consumes all arguments.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/ident.h>
 * #include <metalang99/variadics.h>
 *
 * #define F_IMPL(x) v([x])
 * #define F_ARITY   1
 *
 * // [a] [b] [c] ... [x] [y] [z]
 * ML99_variadicsForEach(v(F), v(ML99_LOWERCASE_CHARS()))
 * @endcode
 */
/**
 * The same as #ML99_LOWERCASE_CHARS but for uppercase characters.
 */
/**
 * The same as #ML99_LOWERCASE_CHARS but for digits.
 */
// Arity specifiers {
// } (Arity specifiers)

/**
 * The left value @p x.
 */
/**
 * The right value @p x.
 */
/**
 * `ML99_true()` if @p either contains a left value, otherwise `ML99_false()`.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/either.h>
 *
 * // 1
 * ML99_isLeft(ML99_left(v(123)))
 *
 * // 0
 * ML99_isLeft(ML99_right(v(123)))
 * @endcode
 */
/**
 * The inverse of #ML99_isLeft.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/either.h>
 *
 * // 1
 * ML99_isRight(ML99_right(v(123)))
 *
 * // 0
 * ML99_isRight(ML99_left(v(123)))
 * @endcode
 */
/**
 * Tests @p either and @p other for equality.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/either.h>
 * #include <metalang99/nat.h>
 *
 * // 1
 * ML99_eitherEq(v(ML99_natEq), ML99_left(v(123)), ML99_left(v(123)))
 *
 * // 0
 * ML99_eitherEq(v(ML99_natEq), ML99_right(v(123)), ML99_left(v(8)))
 *
 * // 0
 * ML99_eitherEq(v(ML99_natEq), ML99_right(v(123)), ML99_left(v(123)))
 * @endcode
 */
/**
 * Returns the left value on `ML99_left(x)` or emits a fatal error on `ML99_right(y)`.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/either.h>
 *
 * // 123
 * ML99_unwrapLeft(ML99_left(v(123)))
 *
 * // Emits a fatal error.
 * ML99_unwrapLeft(ML99_right(v(123)))
 * @endcode
 */
/**
 * The inverse of #ML99_unwrapLeft.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/either.h>
 *
 * // 123
 * ML99_unwrapRight(ML99_right(v(123)))
 *
 * // Emits a fatal error.
 * ML99_unwrapRight(ML99_left(v(123)))
 * @endcode
 */
// ML99_eitherEq_IMPL {
// } (ML99_eitherEq_IMPL)
// Arity specifiers {
// } (Arity specifiers)
/**
 * @file
 * Support for C language constructions.
 *
 * Some decent usage examples can be found in
 * [datatype99/examples/derive](https://github.com/Hirrolot/datatype99/tree/master/examples/derive).
 */
/**
 * @file
 * Cons-lists.
 */
/**
 * @file
 * Natural numbers: [0; 255].
 *
 * Most of the time, natural numbers are used for iteration; they are not meant for CPU-bound tasks
 * such as Fibonacci numbers or factorials.
 */
/**
 * @file
 * An optional value.
 */
/**
 * Some value @p x.
 */
/**
 * No value.
 */
/**
 * `ML99_true()` if @p maybe contains some value, otherwise `ML99_false()`.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/maybe.h>
 *
 * // 1
 * ML99_isJust(ML99_just(v(123)))
 *
 * // 0
 * ML99_isJust(ML99_nothing())
 * @endcode
 */
/**
 * The inverse of #ML99_isJust.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/maybe.h>
 *
 * // 1
 * ML99_isNothing(ML99_nothing())
 *
 * // 0
 * ML99_isNothing(ML99_just(v(123)))
 * @endcode
 */
/**
 * Tests @p maybe and @p other for equality.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/maybe.h>
 * #include <metalang99/nat.h>
 *
 * // 1
 * ML99_maybeEq(v(ML99_natEq), ML99_just(v(123)), ML99_just(v(123)));
 *
 * // 0
 * ML99_maybeEq(v(ML99_natEq), ML99_just(v(4)), ML99_just(v(6)));
 *
 * // 0
 * ML99_maybeEq(v(ML99_natEq), ML99_just(v(4)), ML99_nothing());
 * @endcode
 */
/**
 * Returns the contained value on `ML99_just(x)` or emits a fatal error on `ML99_nothing()`.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/maybe.h>
 *
 * // 123
 * ML99_maybeUnwrap(ML99_just(v(123)))
 *
 * // Emits a fatal error.
 * ML99_maybeUnwrap(ML99_nothing())
 * @endcode
 */
// ML99_maybeEq_IMPL {
// } (ML99_maybeEq_IMPL)
// Arity specifiers {
// } (Arity specifiers)
/**
 * @file
 * Tuples: `(x, y, z)`.
 *
 * A tuple is represented as `(x1, ..., xN)`. Tuples are a convenient way to deal with product
 * types. For example:
 *
 * [[examples/rectangle.c](https://github.com/Hirrolot/metalang99/blob/master/examples/rectangle.c)]
 * @include rectangle.c
 *
 * @note Tuples are more time and space-efficient than lists, but export less functionality; if a
 * needed function is missed, invoking #ML99_list and then manipulating with the resulting Cons-list
 * might be helpful.
 */
/**
 * @file
 * Variadic arguments: `x, y, z`.
 *
 * @note Variadics are more time and space-efficient than lists, but export less functionality; if a
 * needed function is missed, invoking #ML99_list and then manipulating with the resulting Cons-list
 * might be helpful.
 */
/**
 * Computes a count of its arguments.
 *
 * At most 63 arguments are acceptable.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/variadics.h>
 *
 * // 3
 * ML99_variadicsCount(v(~, ~, ~))
 *
 * // 1
 * ML99_variadicsCount()
 * @endcode
 */
/**
 * Tells if it received only one argument or not.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/variadics.h>
 *
 * // 1
 * ML99_variadicsIsSingle(v(~))
 *
 * // 0
 * ML99_variadicsIsSingle(v(~, ~, ~))
 * @endcode
 */
/**
 * Expands to a metafunction extracting the @p i -indexed argument.
 *
 * @p i can range from 0 to 7, inclusively.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/variadics.h>
 *
 * // 2
 * ML99_variadicsGet(1)(v(1, 2, 3))
 * @endcode
 */
/**
 * Extracts the tail of its arguments.
 *
 * At least two arguments must be specified.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/variadics.h>
 *
 * // 2, 3
 * ML99_variadicsTail(v(1, 2, 3))
 * @endcode
 */
/**
 * Applies @p f to each argument.
 *
 * The result is `ML99_appl(f, x1) ... ML99_appl(f, xN)`.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/variadics.h>
 *
 * #define F_IMPL(x) v(@x)
 * #define F_ARITY   1
 *
 * // @x @y @z
 * ML99_variadicsForEach(v(F), v(x, y, z))
 * @endcode
 */
/**
 * Applies @p f to each argument with an index.
 *
 * The result is `ML99_appl2(f, x1, 0) ... ML99_appl2(f, xN, N - 1)`.
 *
 * @code
 * #include <metalang99/variadics.h>
 *
 * #define F_IMPL(x, i) v(@x##i)
 * #define F_ARITY      2
 *
 * // @x0 @y1 @z2
 * ML99_variadicsForEachI(v(F), v(x, y, z))
 * @endcode
 */
/**
 * Overloads @p f on a number of arguments.
 *
 * This function counts the number of provided arguments, appends it to @p f and calls the resulting
 * macro identifier with provided arguments.
 *
 * At most 63 variadic arguments are acceptable.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/variadics.h>
 *
 * #define X(...)    ML99_OVERLOAD(X_, __VA_ARGS__)
 * #define X_1(a)    Billie & a
 * #define X_2(a, b) Jean & a & b
 *
 * // Billie & 4
 * X(4)
 *
 * // Jean & 5 & 6
 * X(5, 6)
 * @endcode
 *
 * @note @p f need not be postfixed with `_IMPL`. It is literally invoked as `ML99_CAT(f,
 * ML99_VARIADICS_COUNT(...))(...)`.
 */
// ML99_variadicsForEach_IMPL {
// } (ML99_variadicsForEach_IMPL)
// ML99_variadicsForEachI_IMPL {
// } (ML99_variadicsForEachI_IMPL)
/*
 * The StackOverflow solution: <https://stackoverflow.com/a/2124385/13166656>.
 *
 * This macro supports at most 63 arguments because C99 allows implementations to handle only 127
 * parameters/arguments per macro definition/invocation (C99 | 5.2.4 Environmental limits), and
 * `ML99_PRIV_VARIADICS_COUNT_AUX` already accepts 64 arguments.
 */
// clang-format off
// clang-format on
// Arity specifiers {
// } (Arity specifiers)

/**
 * Transforms a sequence of arguments into `(...)`.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/tuple.h>
 *
 * // (1, 2, 3)
 * ML99_tuple(v(1, 2, 3))
 * @endcode
 */
/**
 * Transforms a sequence of arguments into `(v(...))`.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/tuple.h>
 *
 * // (v(1, 2, 3))
 * ML99_tupleEval(v(1, 2, 3))
 * @endcode
 *
 * @deprecated I have seen no single use case over time. Please, [open an
 * issue](https://github.com/Hirrolot/metalang99/issues/new/choose) if you need this function.
 */
/**
 * Untuples the tuple @p x, leaving the result unevaluated.
 *
 * If @p x is not a tuple, it emits a fatal error.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/tuple.h>
 *
 * // 1, 2, 3
 * ML99_untuple(v((1, 2, 3)))
 * @endcode
 */
/**
 * The same as #ML99_untuple.
 *
 * @deprecated Use #ML99_untuple instead.
 */
/**
 * Untuples the tuple @p x and evaluates the result.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/tuple.h>
 *
 * // 1, 2, 3
 * ML99_untupleEval(v((v(1, 2, 3))))
 * @endcode
 *
 * @deprecated For the same reason as #ML99_tupleEval.
 */
/**
 * Tests whether @p x is inside parentheses or not.
 *
 * The preconditions are the same as of #ML99_isUntuple.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/tuple.h>
 *
 * // 0
 * ML99_isTuple(v(123))
 *
 * // 1
 * ML99_isTuple(v((123)))
 * @endcode
 */
/**
 * The inverse of #ML99_isTuple.
 *
 * @p x must be either of these forms:
 *  - `(...)` (reported as non-untupled)
 *  - `(...) (...) ...` (reported as untupled)
 *  - anything else not beginning with `(...)` (reported as untupled)
 *
 * For example (respectively):
 *  - `(~, ~, ~)` (non-untupled)
 *  - `(~, ~, ~) (~, ~, ~)` or `(~, ~, ~) (~, ~, ~) abc` (untupled)
 *  - `123` or `123 (~, ~, ~)` (untupled)
 *
 * # Examples
 *
 * @code
 * #include <metalang99/tuple.h>
 *
 * // 1
 * ML99_isUntuple(v(123))
 *
 * // 0
 * ML99_isUntuple(v((123)))
 *
 * // 1
 * ML99_isUntuple(v((123) (456) (789)))
 * @endcode
 */
/**
 * Computes the count of items in the tuple @p x.
 *
 * At most 63 items can be contained in @p x.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/tuple.h>
 *
 * // 3
 * ML99_tupleCount(v((~, ~, ~)))
 *
 * // 1
 * ML99_tupleCount(v(()))
 * @endcode
 */
/**
 * Tells if the tuple @p x contains only one item or not.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/tuple.h>
 *
 * // 1
 * ML99_tupleIsSingle(v((~)))
 *
 * // 0
 * ML99_tupleIsSingle(v((~, ~, ~)))
 * @endcode
 */
/**
 * Expands to a metafunction extracting the @p i -indexed element of a tuple.
 *
 * @p i can range from 0 to 7, inclusively.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/tuple.h>
 *
 * // 2
 * ML99_tupleGet(1)(v((1, 2, 3)))
 * @endcode
 */
/**
 * Extracts the tuple's tail.
 *
 * @p x must contain at least two elements.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/tuple.h>
 *
 * // 2, 3
 * ML99_tupleTail(v((1, 2, 3)))
 * @endcode
 */
/**
 * Appends provided variadic arguments to the tuple @p x.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/tuple.h>
 *
 * // (1, 2, 3)
 * ML99_tupleAppend(ML99_tuple(v(1)), v(2, 3))
 * @endcode
 */
/**
 * Prepends provided variadic arguments to the tuple @p x.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/tuple.h>
 *
 * // (1, 2, 3)
 * ML99_tuplePrepend(ML99_tuple(v(3)), v(1, 2))
 * @endcode
 */
/**
 * A shortcut for `ML99_variadicsForEach(f, ML99_untuple(x))`.
 */
/**
 * A shortcut for `ML99_variadicsForEachI(f, ML99_untuple(x))`.
 */
/**
 * Emits a fatal error if @p x is not a tuple, otherwise results in emptiness.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/tuple.h>
 *
 * #define F_IMPL(x) ML99_TERMS(ML99_assertIsTuple(v(x)), ML99_untuple(v(x)))
 *
 * // 1, 2, 3
 * ML99_call(F, v((1, 2, 3)))
 *
 * // A compile-time tuple mismatch error.
 * ML99_call(F, v(123))
 * @endcode
 */
// clang-format off
// clang-format on
// Arity specifiers {
// } (Arity specifiers)
/**
 * \f$x + 1\f$
 *
 * # Examples
 *
 * @code
 * #include <metalang99/nat.h>
 *
 * // 6
 * ML99_inc(v(5))
 * @endcode
 *
 * @note If @p x is #ML99_NAT_MAX, the result is 0.
 */
/**
 * \f$x - 1\f$
 *
 * # Examples
 *
 * @code
 * #include <metalang99/nat.h>
 *
 * // 4
 * ML99_dec(v(5))
 * @endcode
 *
 * @note If @p x is 0, the result is #ML99_NAT_MAX.
 */
/**
 * Matches @p x against the two cases: if it is zero or positive.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/nat.h>
 *
 * #define MATCH_Z_IMPL()  v(Billie)
 * #define MATCH_S_IMPL(x) v(Jean ~ x)
 *
 * // Billie
 * ML99_natMatch(v(0), v(MATCH_))
 *
 * // Jean ~ 122
 * ML99_natMatch(v(123), v(MATCH_))
 * @endcode
 *
 * @note This function calls @p f with #ML99_call, so no partial application occurs, and so
 * arity specifiers are not needed.
 */
/**
 * The same as #ML99_natMatch but provides additional arguments to all branches.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/nat.h>
 *
 * #define MATCH_Z_IMPL(x, y, z)    v(Billie ~ x y z)
 * #define MATCH_S_IMPL(n, x, y, z) v(Jean ~ n ~ x y z)
 *
 * // Billie ~ 1 2 3
 * ML99_natMatchWithArgs(v(0), v(MATCH_), v(1, 2, 3))
 *
 * // Jean ~ 122 ~ 1 2 3
 * ML99_natMatchWithArgs(v(123), v(MATCH_), v(1, 2, 3))
 * @endcode
 */
/**
 * \f$x = y\f$
 *
 * # Examples
 *
 * @code
 * #include <metalang99/nat.h>
 *
 * // 1
 * ML99_natEq(v(5), v(5))
 *
 * // 0
 * ML99_natEq(v(3), v(8))
 * @endcode
 */
/**
 * \f$x \neq y\f$
 *
 * # Examples
 *
 * @code
 * #include <metalang99/nat.h>
 *
 * // 0
 * ML99_natNeq(v(5), v(5))
 *
 * // 1
 * ML99_natNeq(v(3), v(8))
 * @endcode
 */
/**
 * \f$x > y\f$
 *
 * # Examples
 *
 * @code
 * #include <metalang99/nat.h>
 *
 * // 1
 * ML99_greater(v(8), v(3))
 *
 * // 0
 * ML99_greater(v(3), v(8))
 * @endcode
 */
/**
 * \f$x \geq y\f$
 *
 * # Examples
 *
 * @code
 * #include <metalang99/nat.h>
 *
 * // 1
 * ML99_greaterEq(v(8), v(8))
 *
 * // 0
 * ML99_greaterEq(v(3), v(8))
 * @endcode
 */
/**
 * \f$x < y\f$
 *
 * # Examples
 *
 * @code
 * #include <metalang99/nat.h>
 *
 * // 1
 * ML99_lesser(v(3), v(8))
 *
 * // 0
 * ML99_lesser(v(8), v(3))
 * @endcode
 */
/**
 * \f$x \leq y\f$
 *
 * # Examples
 *
 * @code
 * #include <metalang99/nat.h>
 *
 * // 1
 * ML99_lesserEq(v(8), v(8))
 *
 * // 0
 * ML99_lesserEq(v(8), v(3))
 * @endcode
 */
/**
 * \f$x + y\f$
 *
 * # Examples
 *
 * @code
 * #include <metalang99/nat.h>
 *
 * // 11
 * ML99_add(v(5), v(6))
 * @endcode
 */
/**
 * \f$x - y\f$
 *
 * # Examples
 *
 * @code
 * #include <metalang99/nat.h>
 *
 * // 6
 * ML99_sub(v(11), v(5))
 * @endcode
 */
/**
 * \f$x * y\f$
 *
 * # Examples
 *
 * @code
 * #include <metalang99/nat.h>
 *
 * // 12
 * ML99_mul(v(3), v(4))
 * @endcode
 */
/**
 * \f$\frac{x}{y}\f$
 *
 * # Examples
 *
 * @code
 * #include <metalang99/nat.h>
 *
 * // 3
 * ML99_div(v(12), v(4))
 * @endcode
 *
 * @note A compile-time error if \f$\frac{x}{y}\f$ is not a natural number.
 */
/**
 * Like #ML99_div but returns `ML99_nothing()` is @p x is not divisible by @p y,
 * otherwise `ML99_just(result)`.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/nat.h>
 *
 * // ML99_just(3)
 * ML99_divChecked(v(12), v(4))
 *
 * // ML99_nothing()
 * ML99_divChecked(v(14), v(5))
 *
 * // ML99_nothing()
 * ML99_divChecked(v(1), v(0))
 * @endcode
 */
/**
 * Computes the remainder of division.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/nat.h>
 *
 * // 2
 * ML99_mod(v(8), v(3))
 * @endcode
 *
 * @note A compile-time error if @p y is 0.
 */
/**
 * \f$x + y + z\f$
 *
 * # Examples
 *
 * @code
 * #include <metalang99/nat.h>
 *
 * // 15
 * ML99_add3(v(1), v(6), v(8))
 * @endcode
 */
/**
 * \f$x - y - z\f$
 *
 * # Examples
 *
 * @code
 * #include <metalang99/nat.h>
 *
 * // 3
 * ML99_sub3(v(8), v(2), v(3))
 * @endcode
 */
/**
 * \f$x * y * z\f$
 *
 * # Examples
 *
 * @code
 * #include <metalang99/nat.h>
 *
 * // 24
 * ML99_mul3(v(2), v(3), v(4))
 * @endcode
 */
/**
 * \f$\frac{(\frac{x}{y})}{z}\f$
 *
 * # Examples
 *
 * @code
 * #include <metalang99/nat.h>
 *
 * // 5
 * ML99_div(v(30), v(3), v(2))
 * @endcode
 *
 * @note A compile-time error if \f$\frac{(\frac{x}{y})}{z}\f$ is not a natural number.
 */
/**
 * \f$min(x, y)\f$
 *
 * # Examples
 *
 * @code
 * #include <metalang99/nat.h>
 *
 * // 5
 * ML99_min(v(5), v(7))
 * @endcode
 */
/**
 * \f$max(x, y)\f$
 *
 * # Examples
 *
 * @code
 * #include <metalang99/nat.h>
 *
 * // 7
 * ML99_max(v(5), v(7))
 * @endcode
 */
/**
 * Emits a fatal error if @p x is not a natural number, otherwise results in emptiness.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/nat.h>
 *
 * #define F_IMPL(x) ML99_TERMS(ML99_assertIsNat(v(x)), ML99_inc(v(x)))
 *
 * // 6
 * ML99_call(F, v(5))
 *
 * // A compile-time number mismatch error.
 * ML99_call(F, v(blah))
 * @endcode
 */
/**
 * The maximum value of a natural number, currently 255.
 */
// Pattern matching {
// } (Pattern matching)
// Comparison operators {
// } (Comparison operators)
// Arithmetical operators {
// ML99_mod_IMPL {
// } (ML99_mod_IMPL)
// } (Arithmetical operators)
// clang-format off
// clang-format on
// Arity specifiers {
// } (Arity specifiers)
/**
 * @file
 * Sequences: `(x)(y)(z)`.
 *
 * A sequence is represented as `(...) (...) ...`. For example, these are sequences:
 *  - `(~, ~, ~)`
 *  - `(1)(2)(3)`
 *  - `(+, -, *, /)(123)(~)`
 *
 * Sequences can represent syntax like `X(...) Y(...) Z(...)`, where `X`, `Y`, and `Z` expand to a
 * [tuple](tuple.html), thereby forming a sequence. A perfect example is
 * [Interface99](https://github.com/Hirrolot/interface99), which allows a user to define a software
 * interface via a number of `vfunc(...)` macro invocations:
 *
 * @code
 * #define Shape_IFACE                      \
 *     vfunc( int, perim, const VSelf)      \
 *     vfunc(void, scale, VSelf, int factor)
 *
 * interface(Shape);
 * @endcode
 *
 * With `vfunc` being defined as follows (simplified):
 *
 * @code
 * #define vfunc(ret_ty, name, ...) (ret_ty, name, __VA_ARGS__)
 * @endcode
 *
 * @note Sequences are more time and space-efficient than lists, but export less functionality; if a
 * needed function is missed, invoking #ML99_listFromSeq and then manipulating with the resulting
 * Cons-list might be helpful.
 */
/**
 * True iff @p seq contains no elements (which means an empty preprocessing lexeme).
 *
 * # Examples
 *
 * @code
 * #include <metalang99/seq.h>
 *
 * // 1
 * ML99_seqIsEmpty(v())
 *
 * // 0
 * ML99_seqIsEmpty(v((~)(~)(~)))
 * @endcode
 */
/**
 * Expands to a metafunction extracting the @p i -indexed element of @p seq.
 *
 * @p i can range from 0 to 7, inclusively.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/seq.h>
 *
 * // 2
 * ML99_seqGet(1)(v((1)(2)(3)))
 * @endcode
 */
/**
 * Extracts the tail of @p seq.
 *
 * @p seq must contain at least one element. If @p seq contains **only** one element, the result is
 * `ML99_empty()`.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/seq.h>
 *
 * // (2)(3)
 * ML99_seqTail(v((1)(2)(3)))
 * @endcode
 */
/**
 * Applies @p f to each element in @p seq.
 *
 * The result is `ML99_appl(f, x1) ... ML99_appl(f, xN)`.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/seq.h>
 *
 * #define F_IMPL(x) v(@x)
 * #define F_ARITY   1
 *
 * // @x @y @z
 * ML99_seqForEach(v(F), v((x)(y)(z)))
 * @endcode
 */
/**
 * Applies @p f to each element in @p seq with an index.
 *
 * The result is `ML99_appl2(f, 0, x1) ... ML99_appl2(f, N - 1, xN)`.
 *
 * @code
 * #include <metalang99/seq.h>
 *
 * #define F_IMPL(i, x) v(@x##i)
 * #define F_ARITY      2
 *
 * // @x0 @y1 @z2
 * ML99_seqForEachI(v(F), v((x)(y)(z)))
 * @endcode
 */
// Arity specifiers {
// } (Arity specifiers)
/**
 * @file
 * Utilitary stuff.
 */
/**
 * Concatenates @p a with @p b and evaluates the result.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/util.h>
 *
 * #define ABC123 v(Billie Jean)
 *
 * // Billie Jean
 * ML99_catEval(v(ABC), v(123))
 *
 * // ERROR: 123ABC is not a valid Metalang99 term.
 * ML99_catEval(v(123), v(ABC))
 * @endcode
 *
 * @deprecated I have seen no single use case over time. Please, [open an
 * issue](https://github.com/Hirrolot/metalang99/issues/new/choose) if you need this function.
 */
/**
 * Concatenates @p a with @p b, leaving the result unevaluated.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/util.h>
 *
 * #define ABC123 Billie Jean
 *
 * // Billie Jean
 * ML99_cat(v(ABC), v(123))
 *
 * // 123ABC
 * ML99_cat(v(123), v(ABC))
 * @endcode
 */
/**
 * The same as #ML99_cat but deals with 3 parameters.
 */
/**
 * The same as #ML99_cat but deals with 4 parameters.
 */
/**
 * Stringifies provided arguments.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/util.h>
 *
 * // "Billie Jean"
 * ML99_stringify(v(Billie Jean))
 * @endcode
 */
/**
 * Evaluates to nothing.
 */
/**
 * Evaluates to its arguments.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/util.h>
 *
 * // 1, 2, 3
 * ML99_id(v(1, 2, 3))
 * @endcode
 */
/**
 * Evaluates to @p x, skipping @p a.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/util.h>
 *
 * // 123
 * ML99_const(v(123), v(5))
 * @endcode
 */
/**
 * Reverses the order of arguments of the binary function @p f.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/util.h>
 *
 * // ABC123
 * ML99_appl2(ML99_flip(v(ML99_catUnevaluated)), v(123), v(ABC))
 * @endcode
 */
/**
 * Accepts terms and evaluates them with the space-separator.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/util.h>
 *
 * // 1 2 3
 * ML99_uncomma(ML99_QUOTE(v(1), v(2), v(3)))
 * @endcode
 */
/**
 * Turns @p f into a Metalang99-compliant metafunction with the arity of 1, which can be then called
 * by #ML99_appl.
 *
 * @p f can be any C function or function-like macro.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/util.h>
 * #include <metalang99/variadics.h>
 *
 * #define F(x) @x
 *
 * // @1 @2 @3
 * ML99_variadicsForEach(ML99_reify(v(F)), v(1, 2, 3))
 * @endcode
 *
 * Without #ML99_reify, you would need to write some additional boilerplate:
 *
 * @code
 * #define F_IMPL(x) v(@x)
 * #define F_ARITY   1
 * @endcode
 */
/**
 * Indicates not yet implemented functionality of the macro @p f.
 *
 * #ML99_todo is the same as #ML99_unimplemented except that the former conveys an intent that the
 * functionality is to be implemented later but #ML99_unimplemented makes no such claims.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/util.h>
 *
 * // A not-yet implemented error.
 * ML99_todo(v(F))
 * @endcode
 *
 * @see [Rust's std::todo\!](https://doc.rust-lang.org/core/macro.todo.html) (thanks for the idea!)
 */
/**
 * The same as #ML99_todo but emits a caller-supplied message.
 *
 * @p message must be a string literal.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/util.h>
 *
 * // A not-yet-implemented error.
 * ML99_todoWithMsg(v(F), v("your message"))
 * @endcode
 */
/**
 * Indicates unimplemented functionality of the macro @p f.
 *
 * #ML99_unimplemented is the same as #ML99_todo except that the latter conveys an intent that the
 * functionality is to be implemented later but #ML99_unimplemented makes no such claims.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/util.h>
 *
 * // A not-implemented error.
 * ML99_unimplemented(v(F))
 * @endcode
 *
 * @see [Rust's std::unimplemented\!](https://doc.rust-lang.org/core/macro.unimplemented.html)
 * (thanks for the idea!)
 */
/**
 * The same as #ML99_unimplemented but emits a caller-supplied message.
 *
 * @p message must be a string literal.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/util.h>
 *
 * // A not-implemented error.
 * ML99_unimplementedWithMsg(v(F), v("your message"))
 * @endcode
 */
/**
 * Generates a unique identifier @p id in the namespace @p prefix.
 *
 * Let `FOO` be the name of an enclosing macro. Then `FOO_` must be specified for @p prefix, and @p
 * id should be given any meaningful name (this makes debugging easier).
 *
 * # Examples
 *
 * @code
 * #include <metalang99/util.h>
 *
 * #define FOO(...) FOO_NAMED(ML99_GEN_SYM(FOO_, x), __VA_ARGS__)
 * #define FOO_NAMED(x_sym, ...) \
 *      do { int x_sym = 5; __VA_ARGS__ } while (0)
 *
 * // `x` here will not conflict with the `x` inside `FOO`.
 * FOO({
 *     int x = 7;
 *     printf("x is %d\n", x); // x is 7
 * });
 * @endcode
 *
 * @note Two identical calls to #ML99_GEN_SYM will yield different identifiers, therefore, to refer
 * to the result later, you must save it in an auxiliary macro's parameter, as shown in the example
 * above.
 * @note #ML99_GEN_SYM is defined only if `__COUNTER__` is defined, which must be a macro yielding
 * integral literals starting from 0 incremented by 1 each time it is called. Currently, it is
 * supported at least by Clang, GCC, TCC, and MSVC.
 * @see https://en.wikipedia.org/wiki/Hygienic_macro
 */
/**
 * Forces a caller to put a trailing semicolon.
 *
 * It is useful when defining macros, to make them formatted as complete statements.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/util.h>
 *
 * #define MY_MACRO(fn_name, val_ty, val) \
 *     inline static val_ty fn_name(void) { return val; } \
 *     ML99_TRAILING_SEMICOLON()
 *
 * // Defines a function that always returns 0.
 * MY_MACRO(zero, int, 0);
 * @endcode
 *
 * @note #ML99_TRAILING_SEMICOLON is to be used outside of functions: unlike the `do { ... } while
 * (0)` idiom, this macro expands to a C declaration.
 */
/**
 * Concatenates @p a with @p b as-is, without expanding them.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/util.h>
 *
 * // This macro will not be expanded.
 * #define ABC 7
 *
 * // ABC123
 * ML99_CAT_PRIMITIVE(ABC, 123)
 * @endcode
 */
/**
 * The same as #ML99_CAT_PRIMITIVE but deals with 3 parameters.
 */
/**
 * The same as #ML99_CAT_PRIMITIVE but deals with 4 parameters.
 */
/**
 * Stringifies @p x as-is, without expanding it.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/util.h>
 *
 * // This macro will not be expanded.
 * #define ABC 7
 *
 * // "ABC"
 * ML99_STRINGIFY_PRIMITIVE(ABC)
 * @endcode
 */
/**
 * Expands to an opening parenthesis (`(`).
 *
 * This is helpful when you want to delay macro arguments passing: just type `BAR ML99_LPAREN()
 * initial args...` at the end of some macro `FOO` and complete the invocation of `BAR` with
 * `the rest of args...)` in future.
 *
 * This macro consumes all its arguments.
 *
 * @deprecated This macro results in code that is difficult to reason about.
 */
/**
 * The same as #ML99_LPAREN but emits a closing parenthesis.
 *
 * @deprecated For the same reason as #ML99_LPAREN.
 */
/**
 * Expands to a single comma, consuming all arguments.
 */
/**
 * If you are compiling on GCC, this macro expands to `_Pragma(str)`, otherwise to emptiness.
 */
/**
 * The same as #ML99_GCC_PRAGMA but for Clang.
 */
// clang-format off
// clang-format on
// Arity specifiers {
// } (Arity specifiers)
/**
 * Prepends @p x to @p xs.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/list.h>
 *
 * ML99_cons(v(1), ML99_cons(v(2), ML99_nil()))
 * @endcode
 */
/**
 * The empty list.
 */
/**
 * Checks @p list for non-emptiness.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/list.h>
 *
 * // 1
 * ML99_isCons(ML99_list(v(1, 2, 3)))
 *
 * // 0
 * ML99_isCons(ML99_nil())
 * @endcode
 */
/**
 * Checks @p list for emptiness.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/list.h>
 *
 * // 0
 * ML99_isNil(ML99_list(v(1, 2, 3)))
 *
 * // 1
 * ML99_isNil(ML99_nil())
 * @endcode
 */
/**
 * Extracts the head from the non-empty list @p list.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/list.h>
 *
 * // 1
 * ML99_listHead(ML99_list(v(1, 2, 3)))
 * @endcode
 */
/**
 * Extracts the tail from the non-empty list @p list.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/list.h>
 *
 * // 2, 3
 * ML99_listTail(ML99_list(v(1, 2, 3)))
 *
 * // ML99_nil()
 * ML99_listTail(ML99_list(v(1)))
 * @endcode
 */
/**
 * Extracts the last element from the non-empty list @p list.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/list.h>
 *
 * // 3
 * ML99_listLast(ML99_list(v(1, 2, 3)))
 * @endcode
 */
/**
 * Extracts all the elements of the non-empty list @p list except the last one.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/list.h>
 *
 * // 1, 2
 * ML99_listInit(ML99_list(v(1, 2, 3)))
 *
 * // ML99_nil()
 * ML99_listInit(ML99_list(v(1)))
 * @endcode
 */
/**
 * Constructs a list from its arguments.
 *
 * At most 63 arguments are acceptable.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/list.h>
 *
 * // 1, 2, 3
 * ML99_list(v(1, 2, 3))
 * @endcode
 */
/**
 * Constructs a list from comma-separated [tuples](tuple.html).
 *
 * It sequentially applies @p f to each untupled argument, thus forming the resulting list. If some
 * argument is not a tuple, a fatal error is emitted.
 *
 * The result is `ML99_list(ML99_appl(f, ML99_untuple(x1)), ..., ML99_appl(f, ML99_untuple(xN)))`.
 *
 * Each variadic argument inherits all the preconditions of #ML99_isUntuple.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/list.h>
 *
 * #define F_IMPL(x, y) v(x + y)
 * #define F_ARITY      1
 *
 * // ML99_list(v(1 + 2, 3 + 4, 5 + 6))
 * ML99_listFromTuples(v(F), v((1, 2), (3, 4), (5, 6)))
 * @endcode
 */
/**
 * Constructs a list from the [sequence](seq.html) @p seq.
 *
 * Note that @p seq items must **not** contain commas. If you want commas in items, such as `(+, -,
 * *, /)`, consider wrapping an item in parentheses: `((+, -, *, /))`.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/list.h>
 *
 * // ML99_nil()
 * ML99_listFromSeq(v())
 *
 * // ML99_list(v(1, 2, 3))
 * ML99_listFromSeq(v((1)(2)(3)))
 * @endcode
 */
/**
 * Computes the length of @p list.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/list.h>
 *
 * // 0
 * ML99_listLen(ML99_nil())
 *
 * // 3
 * ML99_listLen(ML99_list(v(1, 2, 3)))
 * @endcode
 */
/**
 * Evaluates a metaprogram that reduces to a list, then unwraps it.
 *
 * It behaves the same as the composition of #ML99_EVAL and #ML99_listUnwrap.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/list.h>
 *
 * // Literally 1 2 3
 * ML99_LIST_EVAL(ML99_list(v(1, 2, 3)))
 * @endcode
 *
 * @note This macro does not result in a Metalang99 term; it literally pastes list elements into a
 * source file.
 */
/**
 * The same as #ML99_LIST_EVAL but intersperses a comma between list items.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/util.h>
 *
 * // Literally 1, 2, 3
 * ML99_LIST_EVAL_COMMA_SEP(ML99_list(v(1, 2, 3)))
 * @endcode
 *
 * @note This macro does not result in a Metalang99 term; it literally pastes comma-separated list
 * elements into a source file.
 */
/**
 * Appends the list @p other to @p list.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/list.h>
 *
 * // 1, 2, 3
 * ML99_listAppend(ML99_list(v(1)), ML99_list(v(2, 3)))
 * @endcode
 */
/**
 * Appends the item @p item to @p list.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/list.h>
 *
 * // 1, 2, 3
 * ML99_listAppendItem(v(3), ML99_list(v(1, 2)))
 * @endcode
 */
/**
 * Places all the items in @p list as-is.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/list.h>
 *
 * // Literally 1 2 3
 * ML99_listUnwrap(ML99_list(v(1, 2, 3)))
 * @endcode
 *
 * @note The resulting value is still a valid Metalang99 term that need to be evaluated further.
 * @see #ML99_LIST_EVAL
 * @see #ML99_LIST_EVAL_COMMA_SEP
 */
/**
 * Places all the items in @p list as-is, separated by commas.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/list.h>
 *
 * // Literally 1, 2, 3
 * ML99_listUnwrapCommaSep(ML99_list(v(1, 2, 3)))
 * @endcode
 *
 * @note The resulting value is still a valid Metalang99 term that need to be evaluated further.
 * @see #ML99_LIST_EVAL
 * @see #ML99_LIST_EVAL_COMMA_SEP
 */
/**
 * Reverses the order of items in @p list.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/list.h>
 *
 * // 3, 2, 1
 * ML99_listReverse(ML99_list(v(1, 2, 3)))
 * @endcode
 */
/**
 * Extracts the @p i -indexed element.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/list.h>
 *
 * // 2
 * ML99_listGet(v(1), ML99_list(v(1, 2, 3)))
 * @endcode
 */
/**
 * A right-associative fold over @p list.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/list.h>
 *
 * #define ABCDEFG 123
 *
 * // 7
 * ML99_listFoldr(v(ML99_cat), v(7), ML99_nil())
 *
 * // 123
 * ML99_listFoldr(ML99_appl(v(ML99_flip), v(ML99_cat)), v(A), ML99_list(v(G, DEF, BC)))
 * @endcode
 */
/**
 * A left-associative fold over @p list.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/list.h>
 *
 * #define ABCDEFG 123
 *
 * // 7
 * ML99_listFoldl(v(ML99_cat), v(7), ML99_nil())
 *
 * // 123
 * ML99_listFoldl(v(ML99_cat), v(A), ML99_list(v(BC, DEF, G)))
 * @endcode
 */
/**
 * The same as #ML99_listFoldl but treats the first element of @p list as the initial value.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/list.h>
 *
 * #define ABCDEFG 123
 *
 * // 123
 * ML99_listFoldl1(v(ML99_cat), ML99_list(v(AB, CDEF, G)))
 * @endcode
 */
/**
 * Intersperses @p item between the items in @p list.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/list.h>
 *
 * // 1, +, 2, +, 3
 * ML99_listIntersperse(v(+), ML99_list(v(1, 2, 3)))
 * @endcode
 */
/**
 * Prepends @p item to all items in @p list.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/list.h>
 *
 * // +, 1, +, 2, +, 3
 * ML99_listPrependToAll(v(+), ML99_list(v(1, 2, 3)))
 * @endcode
 */
/**
 * Maps all the elements in @p list with @p f.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/list.h>
 * #include <metalang99/nat.h>
 *
 * // 4, 5, 6
 * ML99_listMap(ML99_appl(v(ML99_add), v(3)), ML99_list(v(1, 2, 3)))
 * @endcode
 */
/**
 * The same as #ML99_listMap but provides an index of an element to @p f.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/list.h>
 *
 * #define F_IMPL(x, i) v(x[i])
 * #define F_ARITY      2
 *
 * // a[0], b[1], c[2]
 * ML99_listMapI(v(F), ML99_list(v(a, b, c)))
 * @endcode
 */
/**
 * A more efficient version of `ML99_listUnwrap(ML99_listMap(f, list))`.
 *
 * @note Unlike #ML99_listMap, @p f can evaluate to many terms.
 */
/**
 * A more efficient version of `ML99_listUnwrap(ML99_listMapI(f, list))`.
 *
 * @note Unlike #ML99_listMapI, @p f can evaluate to many terms.
 */
/**
 * The same as #ML99_listMap but with the reversed order of arguments.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/list.h>
 * #include <metalang99/nat.h>
 *
 * // 4, 5, 6
 * ML99_listFor(ML99_list(v(1, 2, 3)), ML99_appl(v(ML99_add), v(3)))
 * @endcode
 */
/**
 * Maps the initial elements of the non-empty list @p list with @p f_init and the last element with
 * @p f_last.
 *
 * # Examples
 *
 * @code
 * // 4, 5, 10
 * ML99_listMapInitLast(ML99_appl(v(ML99_add), v(3)), ML99_appl(v(ML99_add), v(7)), ML99_list(v(1,
 * 2, 3)))
 * @endcode
 */
/**
 * The same as #ML99_listMapInitLast but accepts @p list as the first parameter.
 *
 * # Examples
 *
 * @code
 * // 4, 5, 10
 * ML99_listForInitLast(ML99_list(v(1, 2, 3)), ML99_appl(v(ML99_add), v(3)), ML99_appl(v(ML99_add),
 * v(7)))
 * @endcode
 */
/**
 * Filters @p list with @p f.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/list.h>
 * #include <metalang99/nat.h>
 *
 * // 9, 11, 6
 * ML99_listFilter(ML99_appl(v(ML99_lesser), v(5)), ML99_list(v(9, 1, 11, 6, 0, 4)))
 * @endcode
 */
/**
 * A combination of #ML99_listFilter and #ML99_listMap.
 *
 * It builds a new list by applying @p f to each element in @p list: if @p f yields `ML99_just(x)`,
 * `x` is passed to the new list, otherwise (`ML99_nothing()`), the value is neglected.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/list.h>
 * #include <metalang99/maybe.h>
 *
 * #define MAYBE_LIST ML99_list(ML99_just(v(5)), ML99_nothing(), ML99_just(v(7)))
 *
 * // 5, 7
 * ML99_listFilterMap(v(ML99_id), MAYBE_LIST)
 * @endcode
 */
/**
 * Tests @p list and @p other for equality.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/list.h>
 * #include <metalang99/nat.h>
 *
 * // 0
 * ML99_listEq(v(ML99_natEq), ML99_list(v(1, 2, 3)), ML99_list(v(4, 5, 6)))
 *
 * // 1
 * ML99_listEq(v(ML99_natEq), ML99_list(v(1, 2, 3)), ML99_list(v(1, 2, 3)))
 * @endcode
 */
/**
 * Checks whether @p item resides in @p list.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/list.h>
 * #include <metalang99/nat.h>
 *
 * // 1
 * ML99_listContains(v(ML99_natEq), v(3), ML99_list(v(1, 2, 3)))
 *
 * // 0
 * ML99_listContains(v(ML99_natEq), v(456), ML99_list(v(1, 2, 3)))
 * @endcode
 */
/**
 * Extracts the prefix of @p list of the length @p n. If @p n is greater than the length of @p list,
 * the whole @p list is returned.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/list.h>
 *
 * // 1, 2
 * ML99_listTake(v(2), ML99_list(v(1, 2, 3)))
 * @endcode
 */
/**
 * Extracts the items from @p list as long as @p f evaluates to `ML99_true()`.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/list.h>
 * #include <metalang99/nat.h>
 *
 * // 1, 2, 3
 * ML99_listTakeWhile(ML99_appl(v(ML99_greater), v(4)), ML99_list(v(1, 2, 3, 4, 5, 6)))
 * @endcode
 */
/**
 * Removes the prefix of @p list of the length @p n. If @p n is greater than the length of @p list,
 * `ML99_nil()` is returned.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/list.h>
 *
 * // 2, 3
 * ML99_listDrop(v(1), ML99_list(v(1, 2, 3)))
 * @endcode
 */
/**
 * Removes the items from @p list as long as @p f evaluates to `ML99_true()`.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/list.h>
 * #include <metalang99/nat.h>
 *
 * // 4, 5, 6
 * ML99_listDropWhile(ML99_appl(v(ML99_lesser), v(4)), ML99_list(v(1, 2, 3, 4, 5, 6)))
 * @endcode
 */
/**
 * Computes a list of two-place tuples of the corresponding items from @p list and @p other.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/list.h>
 *
 * // (1, 4), (2, 5), (3, 6)
 * ML99_listZip(ML99_list(v(1, 2, 3)), ML99_list(v(4, 5, 6)))
 * @endcode
 */
/**
 * Transforms a list of two-place tuples into a tuple of a list of the first components and a list
 * of the second components.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/list.h>
 * #include <metalang99/tuple.h>
 *
 * // ML99_tuple(ML99_list(v(1, 2, 3)), ML99_list(v(4, 5, 6)))
 * ML99_listUnzip(ML99_list(ML99_tuple(v(1, 4)), ML99_tuple(v(2, 5)), ML99_tuple(v(3, 6))))
 * @endcode
 */
/**
 * Computes a list of length @p n with each element @p item.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/list.h>
 *
 * // ~, ~, ~, ~, ~
 * ML99_listReplicate(v(5), v(~))
 *
 * // ML99_nil()
 * ML99_listReplicate(v(0), v(~))
 * @endcode
 */
/**
 * Returns a two-place tuple of lists: those items of @p list the do and do not satisfy the
 * predicate @p f, respectively.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/list.h>
 * #include <metalang99/nat.h>
 *
 * // ML99_tuple(ML99_list(v(4, 7)), ML99_list(v(11, 12, 13)))
 * ML99_listPartition(ML99_appl(v(ML99_greater), v(10)), ML99_list(v(11, 4, 12, 13, 7)))
 * @endcode
 */
/**
 * Applies all the items in @p list to @p f.
 *
 * If the list is empty, results in @p f as-is.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/list.h>
 * #include <metalang99/nat.h>
 *
 * // ML99_add
 * ML99_listAppl(v(ML99_add), ML99_nil())
 *
 * // ML99_appl(v(ML99_add), v(1))
 * ML99_listAppl(v(ML99_add), ML99_list(v(1)))
 *
 * // ML99_appl2(v(ML99_add), v(1), v(2))
 * ML99_listAppl(v(ML99_add), ML99_list(v(1, 2)))
 * @endcode
 */
// ML99_list_IMPL {
// Last 4 recursion steps unrolled.
// } (ML99_list_IMPL)
// ML99_listFromTuples_IMPL {
// } (ML99_listFromTuples_IMPL)
// ML99_listFilter_IMPL {
// } (ML99_listFilter_IMPL)
// ML99_listFilterMap_IMPL {
// } (ML99_listFilterMap_IMPL)
// ML99_listEq_IMPL {
// } (ML99_listEq_IMPL)
// ML99_listTakeWhile_IMPL {
// } (ML99_listTakeWhile_IMPL)
// ML99_listDropWhile_IMPL {
// } (ML99_listDropWhile_IMPL)
// ML99_listZip_IMPL {
// } (ML99_listZip_IMPL)
// ML99_listUnzip_IMPL {
// } (ML99_listUnzip_IMPL)
// ML99_listPartition_IMPL {
// } (ML99_listPartition_IMPL)
// ML99_listUnwrapCommaSep_IMPL {
// } (ML99_listUnwrapCommaSep_IMPL)
// clang-format off
// clang-format on
// Arity specifiers {
// } (Arity specifiers)
/**
 * @file
 * Statement chaining.
 *
 * This module exports a bunch of so-called _statement chaining macros_: they expect a statement
 * right after their invocation, and moreover, an invocation of such a macro with a statement
 * afterwards altogether form a single statement.
 *
 * How can this be helpful? Imagine you are writing a macro with the following syntax:
 *
 * @code
 * MY_MACRO(...) { bla bla bla }
 * @endcode
 *
 * Then `MY_MACRO` must expand to a _statement prefix_, i.e., something that expects a statement
 * after itself. One possible solution is to make `MY_MACRO` expand to a sequence of statement
 * chaining macros like this:
 *
 * @code
 * #define MY_MACRO(...) \
 *     ML99_INTRODUCE_VAR_TO_STMT(int x = 5) \
 *         ML99_CHAIN_EXPR_STMT(printf("%d\n", x)) \
 *             // and so on...
 * @endcode
 *
 * Here #ML99_INTRODUCE_VAR_TO_STMT accepts the statement formed by #ML99_CHAIN_EXPR_STMT, which, in
 * turn, accepts the next statement and so on, until a caller of `MY_MACRO` specifies the final
 * statement, thus completing the chain.
 *
 * @see https://www.chiark.greenend.org.uk/~sgtatham/mp/ for a more involved explanation.
 */
/**
 * A statement chaining macro that introduces several variable definitions to a statement right
 * after its invocation.
 *
 * Variable definitions must be specified as in the first clause of the for-loop.
 *
 * Top-level `break`/`continue` inside a user-provided statement are prohibited.
 *
 * # Example
 *
 * @code
 * #include <metalang99/stmt.h>
 *
 * for (int i = 0; i < 10; i++)
 *     ML99_INTRODUCE_VAR_TO_STMT(double x = 5.0, y = 7.0)
 *         if (i % 2 == 0)
 *             printf("i = %d, x = %f, y = %f\n", i, x, y);
 * @endcode
 */
/**
 * The same as #ML99_INTRODUCE_VAR_TO_STMT but deals with a single non-`NULL` pointer.
 *
 * In comparison with #ML99_INTRODUCE_VAR_TO_STMT, this macro generates a little less code. It
 * introduces a pointer to @p ty identified by @p name and initialised to @p init.
 *
 * Top-level `break`/`continue` inside a user-provided statement are prohibited.
 *
 * # Example
 *
 * @code
 * #include <metalang99/stmt.h>
 *
 * double x = 5.0, y = 7.0;
 *
 * for (int i = 0; i < 10; i++)
 *     ML99_INTRODUCE_NON_NULL_PTR_TO_STMT(double, x_ptr, &x)
 *         ML99_INTRODUCE_NON_NULL_PTR_TO_STMT(double, y_ptr, &y)
 *             printf("i = %d, x = %f, y = %f\n", i, *x_ptr, *y_ptr);
 * @endcode
 *
 * @note Unlike #ML99_INTRODUCE_VAR_TO_STMT, the generated pointer is guaranteed to be used at least
 * once, meaning that you do not need to suppress the unused variable warning.
 * @note @p init is guaranteed to be executed only once.
 */
/**
 * A statement chaining macro that executes an expression statement derived from @p expr right
 * before the next statement.
 *
 * Top-level `break`/`continue` inside a user-provided statement are prohibited.
 *
 * # Example
 *
 * @code
 * #include <metalang99/stmt.h>
 *
 * int x;
 *
 * for(;;)
 *     ML99_CHAIN_EXPR_STMT(x = 5)
 *         ML99_CHAIN_EXPR_STMT(printf("%d\n", x))
 *             puts("abc");
 * @endcode
 */
/**
 * The same as #ML99_CHAIN_EXPR_STMT but executes @p expr **after** the next statement.
 */
/**
 * A statement chaining macro that suppresses the "unused X" warning right before a statement after
 * its invocation.
 *
 * Top-level `break`/`continue` inside a user-provided statement are prohibited.
 *
 * # Example
 *
 * @code
 * #include <metalang99/stmt.h>
 *
 * int x, y;
 *
 * for(;;)
 *     ML99_SUPPRESS_UNUSED_BEFORE_STMT(x)
 *         ML99_SUPPRESS_UNUSED_BEFORE_STMT(y)
 *             puts("abc");
 * @endcode
 *
 * @deprecated Use `ML99_CHAIN_EXPR_STMT((void)expr)` instead.
 */
// See <https://github.com/Hirrolot/metalang99/issues/25>.
/**
 * Puts a semicolon after provided arguments.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/gen.h>
 *
 * // int x = 5;
 * ML99_semicoloned(v(int x = 5))
 * @endcode
 */
/**
 * Puts provided arguments into braces.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/gen.h>
 *
 * // { int a, b, c; }
 * ML99_braced(v(int a, b, c;))
 * @endcode
 */
/**
 * Generates an assignment of provided variadic arguments to @p lhs.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/gen.h>
 *
 * // x = 5, 6, 7
 * ML99_assign(v(x), v(5, 6, 7))
 * @endcode
 */
/**
 * A shortcut for `ML99_assign(lhs, ML99_braced(...))`.
 */
/**
 * A shortcut for `ML99_semicoloned(ML99_assign(lhs, ...))`.
 */
/**
 * A shortcut for `ML99_assignStmt(lhs, ML99_braced(...))`.
 */
/**
 * Generates a function/macro invocation.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/gen.h>
 *
 * // If you are on C11.
 * ML99_invoke(v(_Static_assert), v(1 == 1, "Must be true"))
 * @endcode
 */
/**
 * A shortcut for `ML99_semicoloned(ML99_invoke(f, ...))`.
 */
/**
 * Generates `prefix { code }`.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/gen.h>
 *
 * // if (1 == 1) {
 * //     printf("x = %d\n", x);
 * // }
 * ML99_prefixedBlock(v(if (1 == 1)), v(printf("x = %d\n", x);))
 * @endcode
 */
/**
 * Generates a type definition.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/gen.h>
 *
 * // typedef struct { int x, y; } Point;
 * ML99_typedef(v(Point), v(struct { int x, y; }))
 * @endcode
 */
/**
 * Generates a C structure.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/gen.h>
 *
 * // struct Point { int x, y; }
 * ML99_struct(v(Point), v(int x, y;))
 * @endcode
 */
/**
 * Generates an anonymous C structure.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/gen.h>
 *
 * // struct { int x, y; }
 * ML99_struct(v(int x, y;))
 * @endcode
 */
/**
 * The same as #ML99_struct but generates a union.
 */
/**
 * The same as #ML99_anonStruct but generates a union.
 */
/**
 * The same as #ML99_struct but generates an enumeration.
 */
/**
 * The same as #ML99_anonStruct but generates an enumeration.
 */
/**
 * Generates a function pointer.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/gen.h>
 *
 * // int (*add)(int x, int y)
 * ML99_fnPtr(v(int), v(add), v(int x), v(int y))
 *
 * // const char *(*title)(void)
 * ML99_fnPtr(v(const char *), v(title), v(void))
 * @endcode
 */
/**
 * A shortcut for `ML99_semicoloned(ML99_fnPtr(ret_ty, name, ...))`.
 */
/**
 * Pastes provided arguments @p n times.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/gen.h>
 *
 * // ~ ~ ~ ~ ~
 * ML99_times(v(5), v(~))
 * @endcode
 */
/**
 * Invokes @p f @p n times, providing an iteration index each time.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/gen.h>
 * #include <metalang99/util.h>
 *
 * // _0 _1 _2
 * ML99_repeat(v(3), ML99_appl(v(ML99_cat), v(_)))
 * @endcode
 */
/**
 * Generates \f$(T_0 \ \_0, ..., T_n \ \_n)\f$.
 *
 * If @p type_list is empty, this macro results in `(void)`.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/gen.h>
 *
 * // (int _0, long long _1, const char * _2)
 * ML99_indexedParams(ML99_list(v(int, long long, const char *)))
 *
 * // (void)
 * ML99_indexedParams(ML99_nil())
 * @endcode
 */
/**
 * Generates \f$T_0 \ \_0; ...; T_n \ \_n\f$.
 *
 * If @p type_list is empty, this macro results in emptiness.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/gen.h>
 *
 * // int _0; long long _1; const char * _2;
 * ML99_indexedFields(ML99_list(v(int, long long, const char *)))
 *
 * // ML99_empty()
 * ML99_indexedFields(ML99_nil())
 * @endcode
 */
/**
 * Generates \f$\{ \_0, ..., \_{n - 1} \}\f$.
 *
 * If @p n is 0, this macro results in `{ 0 }`.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/gen.h>
 *
 * // { _0, _1, _2 }
 * ML99_indexedInitializerList(v(3))
 *
 * // { 0 }
 * ML99_indexedInitializerList(v(0))
 * @endcode
 */
/**
 * Generates \f$\_0, ..., \_{n - 1}\f$.
 *
 * If @p n is 0, this macro results in emptiness.
 *
 * # Examples
 *
 * @code
 * #include <metalang99/gen.h>
 *
 * // _0, _1, _2
 * ML99_indexedArgs(v(3))
 *
 * // ML99_empty()
 * ML99_indexedArgs(v(0))
 * @endcode
 */
// clang-format off
// clang-format on
// ML99_indexedParams_IMPL {
// } (ML99_indexedParams_IMPL)
// ML99_indexedFields_IMPL {
// } (ML99_indexedFields_IMPL)
// Arity specifiers {
// } (Arity specifiers)
/// @deprecated Use `MATCHES` instead.
// Public stuff {
// Metalang99-compliant macros {
// } (Metalang99-compliant macros)
// Attributes manipulation {
// } (Attributes manipulation)
// } (Public stuff)
// Unit type {
typedef char UnitT99;
static const UnitT99 unit_v99 = '\0';
// } (Unit type)
// Sum type generation {
// } (Sum type generation)
// Record type generation {
// } (Record type generation)
// Parse variants {
// } (Parse variants)
// Parse fields {
// } (Parse fields)
// Variant {
// } (Variant)
// Derivation {
// } (Derivation)
// Pattern matching {
// clang-format off
// clang-format on
// clang-format off
// clang-format on
/// @deprecated Use `MATCHES99` instead.
// } (Pattern matching)
/*
 * For each variant:
 *
 * typedef struct <datatype-name> <variant-name>SumT;
 *
 * (For a non-empty variant:)
 * typedef struct <datatype-name><variant-name> {
 *     <type>0 _0;
 *     ...
 *     <type>N _N;
 * } <datatype-name><variant-name>;
 *
 * typedef <type>0 <variant-name>_0;
 * ...
 * typedef <type>N <variant-name>_N;
 */
/*
 * typedef struct <datatype-name><variant-name> {
 *     <type>0 _0;
 *     ...
 *     <type>N _N;
 * } <datatype-name><variant-name>;
 */
/*
 * typedef <type>0 <variant-name>_0;
 * ...
 * typedef <type>N <variant-name>_N;
 */
/*
 * <variant-name>0Tag, ..., <variant-name>NTag
 */
/*
 * <datatype-name><variant-name>0 <variant-name>0;
 * ...
 * <datatype-name><variant-name>N <variant-name>N;
 */
/*
 * inline static <datatype99-name> <variant-name>0(...) { ... }
 * ...
 * inline static <datatype99-name> <variant-name>N(...) { ... }
 */
/*
 * <field-type>0 <field-name>0;
 * ...
 * <field-type>N <field-name>N;
 */
// Compiler-specific stuff {
// } (Compiler-specific stuff)
// Arity specifiers {
// Public:
// } (Arity specifiers)

