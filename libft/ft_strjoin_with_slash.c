#include "libft.h"

/*
 * İki string'i aralarına '/' karakteri koyarak birleştirir.
 * Yeni bir string ayırır (malloc ile).
 * Örnek: ft_strjoin_with_slash("/bin", "ls") -> "/bin/ls"
 */
char    *ft_strjoin_with_slash(char const *s1, char const *s2)
{
    char    *tmp;
    char    *result;

    // s1 veya s2 NULL ise hata döndür
    if (!s1 || !s2)
        return (NULL);
        
    // 1. Adım: s1 ile "/" birleştir (örn: "/bin/")
    tmp = ft_strjoin(s1, "/");
    if (!tmp)
        return (NULL);

    // 2. Adım: (s1 + "/") ile s2 birleştir (örn: "/bin/ls")
    result = ft_strjoin(tmp, s2);
    
    // 1. adımda oluşturulan geçici string'i serbest bırak
    free(tmp);
    
    return (result);
}