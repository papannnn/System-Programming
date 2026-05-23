#ifndef __GLUE_NODE_DLL__
#define __GLUE_NODE_DLL__

struct GlueNodeDLL {
    GlueNodeDLL *right;
    GlueNodeDLL *left;
};

struct GlueDLL {
    GlueNodeDLL *head;
    unsigned int offset;
};

void glueDLLInit(GlueDLL *list, unsigned int offset);
void glueDLLAdd(GlueDLL *lst, GlueNodeDLL *glnode);
void glueDLLRemove(GlueDLL *lst, GlueNodeDLL *glnode);
void glueDLLNodeInit(GlueNodeDLL *node);
void glueDLLForEach(GlueDLL *list, void (*callback) (void* data));

#endif