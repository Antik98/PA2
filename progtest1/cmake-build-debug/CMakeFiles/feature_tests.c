<<<<<<< HEAD

  const char features[] = {"\n"
"C_FEATURE:"
#if ((__clang_major__ * 100) + __clang_minor__) >= 400
"1"
#else
"0"
#endif
"c_function_prototypes\n"
"C_FEATURE:"
#if ((__clang_major__ * 100) + __clang_minor__) >= 400 && defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
"1"
#else
"0"
#endif
"c_restrict\n"
"C_FEATURE:"
#if ((__clang_major__ * 100) + __clang_minor__) >= 400 && defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
"1"
#else
"0"
#endif
"c_static_assert\n"
"C_FEATURE:"
#if ((__clang_major__ * 100) + __clang_minor__) >= 400 && defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
"1"
#else
"0"
#endif
"c_variadic_macros\n"

};

int main(int argc, char** argv) { (void)argv; return features[argc]; }
=======

  const char features[] = {"\n"
"C_FEATURE:"
#if (__GNUC__ * 100 + __GNUC_MINOR__) >= 304
"1"
#else
"0"
#endif
"c_function_prototypes\n"
"C_FEATURE:"
#if (__GNUC__ * 100 + __GNUC_MINOR__) >= 304 && defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
"1"
#else
"0"
#endif
"c_restrict\n"
"C_FEATURE:"
#if (__GNUC__ * 100 + __GNUC_MINOR__) >= 406 && defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201000L
"1"
#else
"0"
#endif
"c_static_assert\n"
"C_FEATURE:"
#if (__GNUC__ * 100 + __GNUC_MINOR__) >= 304 && defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
"1"
#else
"0"
#endif
"c_variadic_macros\n"

};

int main(int argc, char** argv) { (void)argv; return features[argc]; }
>>>>>>> 539200e07c56440f1adef062f86060ee3ea0f4d7
