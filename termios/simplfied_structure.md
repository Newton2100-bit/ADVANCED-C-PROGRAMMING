# this explains the individual members
struct termios {
    tcflag_t c_iflag;   // Input flags
    tcflag_t c_oflag;   // Output flags
    tcflag_t c_lflag;   // Local flags
    tcflag_t c_cflag;   // Control flags
    cc_t c_cc[NCCS];    // Control characters
};
