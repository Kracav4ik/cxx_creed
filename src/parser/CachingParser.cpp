#include "CachingParser.h"

std::shared_ptr<ASTEvent> CachingParser::next_event() {
    if (_next_event < _parser_events.size()) {
        auto event = _parser_events[_next_event];
        ++_next_event;
        return event;
    }
    auto event = _parser.next_event();
    ++_next_event;
    _parser_events.push_back(event);
    return event;
}

CachingParser::CachingParser(ParserBase& parser) : _parser(parser) {}

CachingParser::State CachingParser::state_before_event() {
    return State(*this);
}

void CachingParser::State::drop() {
    _dropped = true;
}

void CachingParser::State::revert() {
    if (!_dropped) {
        _cache_parser._next_event = _next_event;
    }
    drop();
}

CachingParser::State::State(CachingParser& cache_parser) : _cache_parser(cache_parser), _next_event(cache_parser._next_event - 1) {}
