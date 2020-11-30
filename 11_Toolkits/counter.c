#include <glib.h>
#include <stdio.h>

int comparator(const void *w1, const void *w2, void *counter) {
    int a = (int) (long) g_hash_table_lookup(counter, w1);
    int b = (int) (long) g_hash_table_lookup(counter, w2);
    return a < b;
}

int main(int argc, char **argv) {
    GHashTable* counter = g_hash_table_new(g_str_hash, g_str_equal);
	gchar *word;
    char *file = "text.txt", buf[100], **words;
    FILE *f = fopen (file, "r");
    if (!f) {
		printf("Failed to open %s\n", file);
        exit (1);
    }
    while (fgets(buf, sizeof(buf), f)) {
		words = g_strsplit(buf, " ", 0);
        int len = g_strv_length(words);
        if(len == 0) continue;
        for (int i = 0; i < len; i++) {
            word = g_strchomp(words[i]);
            if (strlen(word) == 0) continue;
            if (g_hash_table_lookup(counter, word)) {
                int count = (int) (long) g_hash_table_lookup(counter, word);
                g_hash_table_insert(counter, g_strdup (word), GINT_TO_POINTER (count + 1));
            }
            else {
                g_hash_table_insert(counter, g_strdup (word), GINT_TO_POINTER (1));
            }
        }
    }
    GList *item, *sorted_words = g_hash_table_get_keys(counter);
    sorted_words = g_list_sort_with_data(sorted_words, comparator, counter);
    for(item = sorted_words; item; item = item->next) {
        int count = (int) (long) g_hash_table_lookup(counter, item->data);
        printf("WORD: '%s', COUNT: %d\n", (char *)item->data, GPOINTER_TO_INT(count));
    }
    g_list_free(sorted_words);
    g_hash_table_destroy(counter);
    fclose(f);
	return 0;
}
