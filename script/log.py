#!/usr/bin/env python
import logging


    
log_format = '[%(asctime)s.%(msecs)03d] %(message)s'
date_format="%Y-%m-%d %H:%M:%S"
logging.basicConfig(level=logging.DEBUG,format=log_format,datefmt=date_format)
logger = logging.getLogger(__name__)
logger.setLevel(logging.DEBUG)

def info(msg, *args, **kwargs):
    logger.info(msg, *args, **kwargs)
def debug(msg, *args, **kwargs):
    logger.debug(msg, *args, **kwargs)
def warning(msg, *args, **kwargs):
    logger.warning(msg, *args, **kwargs)
def error(msg, *args, **kwargs):
    logger.error(msg, *args, **kwargs)
