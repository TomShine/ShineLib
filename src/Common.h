#define SAFE_DELETE(p) \
    while (NULL != (p)) {\
        delete p;        \
        p = NULL;        \
    }

#define SAFE_DELETE_ARRAY(p) \
    while (NULL != (p)) {\
        delete [] p;        \
        p = NULL;        \
    }
