#include <malloc.h>
#include <string.h>
#include "tagv2.h"

void add_tag_v2_frame(TagV2* tag, char* id, uint32_t size, uint16_t flags, char* body)
{
    TagV2Frame* new_frame = calloc(1, sizeof(TagV2Frame));

    strcpy(new_frame->header.id, id);

    new_frame->header.size = size;
    new_frame->header.flags = flags;
    new_frame->body = body;

    if (tag->first_frame == NULL) {
        tag->first_frame = new_frame;
    }

    if (tag->last_frame != NULL) {
        tag->last_frame->next = new_frame;
    }

    tag->last_frame = new_frame;
}

TagV2* new_tag_v2(uint16_t version, unsigned char flags, uint32_t size)
{
    TagV2* tag = calloc(1, sizeof(TagV2));

    memcpy(tag->header.id, ID3, 3);

    tag->header.version = version;
    tag->header.flags = flags;
    tag->header.size = size;

    tag->add_frame = add_tag_v2_frame;

    return tag;
}

TagV2Frame* delete_tag_v2_frame(TagV2Frame* frame)
{
    TagV2Frame* next = frame->next;

    if (frame->body != NULL) {
        free(frame->body);
    }

    free(frame);

    return next;
}

void delete_tag_v2(TagV2* tag)
{
    TagV2Frame* frame = tag->first_frame;

    while (frame != NULL) {
        frame = delete_tag_v2_frame(frame);
    }

    free(tag);
}
