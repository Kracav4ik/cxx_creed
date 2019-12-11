#pragma once

#include "ParserBase.h"
#include <vector>

class Parser;
class CachingParser : public ParserBase {
public:
    class State {
    friend class CachingParser;
    public:
        void drop();
        void revert();

    private:
        explicit State(CachingParser& caching_parser);

        CachingParser& _cache_parser;
        size_t _next_event;
        bool _dropped = false;
    };

    explicit CachingParser(ParserBase& parser);
    std::shared_ptr<ASTEvent> next_event() override;
    State state_before_event();

private:
    ParserBase& _parser;
    std::vector<std::shared_ptr<ASTEvent>> _parser_events;
    size_t _next_event = 0;
};
