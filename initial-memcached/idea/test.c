# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

        if (refcount_incr(it) < 2) {
             * other callers can incr the refcount
            if (refcount_incr(search) != 2) {
    // p->written is incremented post-wbuf flush
    refcount_incr(it);
        refcount_incr(it);
         * other callers can incr the refcount. Also skip ourselves. */
        if (refcount_incr(search) != 2) {
    refcount_incr(it);
    /* TODO: if free_chunks below high watermark, increase aggressiveness */
     /* Then perform the following additions. (That is increment each
    APPEND_STAT("incr_misses", "%llu", (unsigned long long)thread_stats.incr_misses);
    APPEND_STAT("incr_hits", "%llu", (unsigned long long)slab_stats.incr_hits);
 * incr  true to increment value, false to decrement
                                    const bool incr, const int64_t delta,
    if (incr) {
    if (incr) {
        c->thread->stats.slab_stats[ITEM_clsid(it)].incr_hits++;
     * increase. */
            fprintf(stderr, "Tried to do incr/decr on invalid item\n");
     * If needed, increase rlimits to allow as many connections
        fprintf(stderr, "Maxconns setting is too low, use -c to increase.\n");
static void complete_incr_bin(conn *c, char *extbuf);
        // +4 need to be here because extbuf is used for protocol_binary_request_incr
            errstr = "Non-numeric server-side value for incr or decr";
static void complete_incr_bin(conn *c, char *extbuf) {
    protocol_binary_response_incr* rsp = (protocol_binary_response_incr*)c->resp->wbuf;
    protocol_binary_request_incr* req = (void *)extbuf;
        fprintf(stderr, "incr ");
        out_of_memory(c, "SERVER_ERROR Out of memory incrementing value");
                c->thread->stats.incr_misses++;
                complete_incr_bin(c, extbuf);
    APPEND_STAT("cmd_incr", "%llu", (unsigned long long)istats.counters[CMD_INCR]);
                /* item_get() has incremented it->refcount for us */
    // If no argument supplied, incr or decr by one.
    bool incr = true; // default mode is to increment.
            incr = true;
            incr = false;
    switch(do_add_delta(c, key, nkey, incr, of.delta, tmpbuf, &of.req_cas_id, hv, &it)) {
        errstr = "CLIENT_ERROR cannot increment or decrement non-numeric value";
            if (incr) {
                c->thread->stats.incr_misses++;
static void process_arithmetic_command(conn *c, token_t *tokens, const size_t ntokens, const bool incr) {
    switch(add_delta(c, key, nkey, incr, delta, temp, NULL)) {
        out_string(c, "CLIENT_ERROR cannot increment or decrement non-numeric value");
        if (incr) {
            c->thread->stats.incr_misses++;
        if (strcmp(tokens[COMMAND_TOKEN].value, "incr") == 0) {
            } else if (strncmp(cm, "incr", 4) == 0) {
        // increase memory by whole megabytes.
 * "item" structure plus space for a small key and value. They increase by
    // increase free count if ITEM_SLABBED
            APPEND_NUM_STAT(i, "incr_hits", "%llu",
                    (unsigned long long)thread_stats.slab_stats[i].incr_hits);
/* refcount == 0 is safe since nobody can incr while item_lock is held.
                    refcount = refcount_incr(it);
            refcount_incr(hdr_it);
    protocol_binary_request_incr *request = (void*)buf;
static enum test_return test_binary_incr_impl(const char* key, uint8_t cmd) {
        protocol_binary_response_incr response;
static enum test_return test_binary_incr(void) {
    return test_binary_incr_impl("test_binary_incr",
static enum test_return test_binary_incrq(void) {
    return test_binary_incr_impl("test_binary_incrq",
    { "binary_incr", test_binary_incr },
    { "binary_incrq", test_binary_incrq },
                                 const size_t nkey, bool incr,
    ret = do_add_delta(c, key, nkey, incr, delta, buf, cas, hv, NULL);